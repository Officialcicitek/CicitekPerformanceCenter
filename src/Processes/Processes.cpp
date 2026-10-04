#include "Processes.h"

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <shellapi.h>

#include <QHash>
#include <QSet>
#include <QString>
#include <QList>

namespace
{
    // =========================================================
    // CPU CACHE
    // =========================================================

    struct CpuSample
    {
        unsigned long long processTime = 0;
        unsigned long long systemTime = 0;
    };

    QHash<unsigned long, CpuSample> previousSamples;

    // =========================================================
    // PROCESS PATH CACHE
    // =========================================================

    struct ProcessPathCache
    {
        QString name;
        QString path;
    };

    QHash<unsigned long, ProcessPathCache> pathCache;

    // =========================================================
    // FILETIME -> UINT64
    // =========================================================

    inline unsigned long long fileTimeToUInt64(
        const FILETIME& fileTime)
    {
        ULARGE_INTEGER value{};

        value.LowPart =
            fileTime.dwLowDateTime;

        value.HighPart =
            fileTime.dwHighDateTime;

        return value.QuadPart;
    }

    // =========================================================
    // SYSTEM CPU TIME
    // =========================================================

    inline unsigned long long getSystemTime()
    {
        FILETIME idleTime{};
        FILETIME kernelTime{};
        FILETIME userTime{};

        if (!GetSystemTimes(
                &idleTime,
                &kernelTime,
                &userTime))
        {
            return 0;
        }

        return
            fileTimeToUInt64(kernelTime) +
            fileTimeToUInt64(userTime);
    }

    // =========================================================
    // PROCESS CPU TIME
    // =========================================================

    inline unsigned long long getProcessTime(
        HANDLE process)
    {
        FILETIME creationTime{};
        FILETIME exitTime{};
        FILETIME kernelTime{};
        FILETIME userTime{};

        if (!GetProcessTimes(
                process,
                &creationTime,
                &exitTime,
                &kernelTime,
                &userTime))
        {
            return 0;
        }

        return
            fileTimeToUInt64(kernelTime) +
            fileTimeToUInt64(userTime);
    }

    // =========================================================
    // CPU USAGE
    // =========================================================

    double calculateCpuUsage(
        unsigned long processId,
        unsigned long long currentProcessTime,
        unsigned long long currentSystemTime)
    {
        if (currentProcessTime == 0 ||
            currentSystemTime == 0)
        {
            return 0.0;
        }

        auto previous =
            previousSamples.find(processId);

        if (previous == previousSamples.end())
        {
            previousSamples.insert(
                processId,
                {
                    currentProcessTime,
                    currentSystemTime
                });

            return 0.0;
        }

        const unsigned long long processDelta =
            currentProcessTime -
            previous->processTime;

        const unsigned long long systemDelta =
            currentSystemTime -
            previous->systemTime;

        previous->processTime =
            currentProcessTime;

        previous->systemTime =
            currentSystemTime;

        if (systemDelta == 0)
        {
            return 0.0;
        }

        double cpu =
            (static_cast<double>(processDelta) /
             static_cast<double>(systemDelta)) *
            100.0;

        if (cpu < 0.0)
            cpu = 0.0;

        if (cpu > 100.0)
            cpu = 100.0;

        return cpu;
    }

    // =========================================================
    // PROCESS PATH
    // =========================================================

    QString getProcessPath(
        HANDLE process,
        unsigned long processId,
        const QString& processName)
    {
        const auto cached =
            pathCache.constFind(processId);

        if (cached != pathCache.constEnd())
        {
            if (cached->name == processName)
            {
                return cached->path;
            }
        }

        wchar_t buffer[32768]{};

        DWORD bufferSize =
            static_cast<DWORD>(
                sizeof(buffer) /
                sizeof(buffer[0]));

        QString path;

        if (QueryFullProcessImageNameW(
                process,
                0,
                buffer,
                &bufferSize))
        {
            path =
                QString::fromWCharArray(
                    buffer,
                    static_cast<int>(bufferSize));
        }

        pathCache.insert(
            processId,
            {
                processName,
                path
            });

        return path;
    }

    // =========================================================
    // CRITICAL WINDOWS PROCESS CHECK
    // =========================================================

    bool isProtectedProcess(
        unsigned long processId,
        const QString& processName)
    {
        if (processId == 0 ||
            processId == 4)
        {
            return true;
        }

        const QString name =
            processName.toLower();

        static const QSet<QString> protectedNames =
        {
            "system",
            "registry",
            "smss.exe",
            "csrss.exe",
            "wininit.exe",
            "services.exe",
            "lsass.exe",
            "winlogon.exe"
        };

        return protectedNames.contains(name);
    }

    // =========================================================
    // PROCESS TREE
    // =========================================================

    QList<unsigned long> getProcessTree(
        unsigned long rootProcessId)
    {
        QList<unsigned long> result;

        if (rootProcessId == 0)
            return result;

        struct ChildProcess
        {
            unsigned long processId = 0;
            unsigned long parentProcessId = 0;
        };

        QList<ChildProcess> allProcesses;

        HANDLE snapshot =
            CreateToolhelp32Snapshot(
                TH32CS_SNAPPROCESS,
                0);

        if (snapshot == INVALID_HANDLE_VALUE)
        {
            return result;
        }

        PROCESSENTRY32W entry{};
        entry.dwSize =
            sizeof(PROCESSENTRY32W);

        if (Process32FirstW(
                snapshot,
                &entry))
        {
            do
            {
                allProcesses.append(
                    {
                        entry.th32ProcessID,
                        entry.th32ParentProcessID
                    });

            } while (Process32NextW(
                snapshot,
                &entry));
        }

        CloseHandle(snapshot);

        QSet<unsigned long> visited;
        visited.insert(rootProcessId);

        bool foundNew = true;

        while (foundNew)
        {
            foundNew = false;

            for (const ChildProcess& process :
                 allProcesses)
            {
                if (!visited.contains(
                        process.parentProcessId))
                {
                    continue;
                }

                if (visited.contains(
                        process.processId))
                {
                    continue;
                }

                visited.insert(
                    process.processId);

                result.append(
                    process.processId);

                foundNew = true;
            }
        }

        return result;
    }
}

// =============================================================
// GET PROCESSES
// =============================================================

QList<ProcessInfo> Processes::getProcesses()
{
    QList<ProcessInfo> processes;
    processes.reserve(256);

    const unsigned long long systemTime =
        getSystemTime();

    QSet<unsigned long> currentPids;

    HANDLE snapshot =
        CreateToolhelp32Snapshot(
            TH32CS_SNAPPROCESS,
            0);

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        return processes;
    }

    PROCESSENTRY32W entry{};
    entry.dwSize =
        sizeof(PROCESSENTRY32W);

    if (Process32FirstW(
            snapshot,
            &entry))
    {
        do
        {
            const unsigned long processId =
                entry.th32ProcessID;

            const QString processName =
                QString::fromWCharArray(
                    entry.szExeFile);

            currentPids.insert(
                processId);

            ProcessInfo info;

            info.name =
                processName;

            info.processId =
                processId;

            info.parentProcessId =
                entry.th32ParentProcessID;

            info.threadCount =
                entry.cntThreads;

            info.status =
                "Running";

            // =================================================
            // PROTECTED PROCESS
            // =================================================

            if (isProtectedProcess(
                    processId,
                    processName))
            {
                info.status =
                    "Protected";
            }

            // =================================================
            // OPEN PROCESS
            // =================================================

            HANDLE process =
                OpenProcess(
                    PROCESS_QUERY_INFORMATION |
                    PROCESS_QUERY_LIMITED_INFORMATION |
                    PROCESS_VM_READ,
                    FALSE,
                    processId);

            if (process)
            {
                // =============================================
                // MEMORY
                // =============================================

                PROCESS_MEMORY_COUNTERS
                    memoryCounters{};

                if (GetProcessMemoryInfo(
                        process,
                        &memoryCounters,
                        sizeof(memoryCounters)))
                {
                    info.memoryUsage =
                        static_cast<unsigned long long>(
                            memoryCounters.WorkingSetSize);
                }

                // =============================================
                // CPU
                // =============================================

                const unsigned long long
                    processTime =
                        getProcessTime(
                            process);

                info.cpuUsage =
                    calculateCpuUsage(
                        processId,
                        processTime,
                        systemTime);

                // =============================================
                // PATH
                // =============================================

                info.path =
                    getProcessPath(
                        process,
                        processId,
                        processName);

                CloseHandle(
                    process);
            }
            else
            {
                info.cpuUsage =
                    0.0;

                if (!isProtectedProcess(
                        processId,
                        processName))
                {
                    info.status =
                        "Access denied";
                }

                // Keep valid cached path.
                const auto cached =
                    pathCache.constFind(
                        processId);

                if (cached != pathCache.constEnd() &&
                    cached->name == processName)
                {
                    info.path =
                        cached->path;
                }
            }

            processes.append(
                info);

        } while (Process32NextW(
            snapshot,
            &entry));
    }

    CloseHandle(
        snapshot);

    // =========================================================
    // CLEAN CPU CACHE
    // =========================================================

    const QList<unsigned long>
        staleCpuPids =
            previousSamples.keys();

    for (const unsigned long pid :
         staleCpuPids)
    {
        if (!currentPids.contains(pid))
        {
            previousSamples.remove(pid);
        }
    }

    // =========================================================
    // CLEAN PATH CACHE
    // =========================================================

    const QList<unsigned long>
        stalePathPids =
            pathCache.keys();

    for (const unsigned long pid :
         stalePathPids)
    {
        if (!currentPids.contains(pid))
        {
            pathCache.remove(pid);
        }
    }

    return processes;
}

// =============================================================
// TERMINATE PROCESS
// =============================================================

bool Processes::terminateProcess(
    unsigned long processId)
{
    if (processId == 0)
        return false;

    // Never terminate protected Windows processes.
    const QList<ProcessInfo> processes =
        getProcesses();

    for (const ProcessInfo& process :
         processes)
    {
        if (process.processId == processId &&
            isProtectedProcess(
                process.processId,
                process.name))
        {
            return false;
        }
    }

    HANDLE process =
        OpenProcess(
            PROCESS_TERMINATE,
            FALSE,
            processId);

    if (!process)
        return false;

    const BOOL result =
        TerminateProcess(
            process,
            1);

    CloseHandle(
        process);

    previousSamples.remove(
        processId);

    pathCache.remove(
        processId);

    return result == TRUE;
}

// =============================================================
// TERMINATE PROCESS TREE
// =============================================================

bool Processes::terminateProcessTree(
    unsigned long processId)
{
    if (processId == 0)
        return false;

    const QList<ProcessInfo> processes =
        getProcesses();

    QString rootName;

    for (const ProcessInfo& process :
         processes)
    {
        if (process.processId == processId)
        {
            rootName =
                process.name;

            break;
        }
    }

    if (rootName.isEmpty())
        return false;

    if (isProtectedProcess(
            processId,
            rootName))
    {
        return false;
    }

    const QList<unsigned long> children =
        getProcessTree(processId);

    bool rootTerminated = false;

    // Terminate children first.
    for (auto it = children.crbegin();
         it != children.crend();
         ++it)
    {
        const unsigned long childPid =
            *it;

        if (childPid == 0 ||
            childPid == 4)
        {
            continue;
        }

        HANDLE child =
            OpenProcess(
                PROCESS_TERMINATE,
                FALSE,
                childPid);

        if (!child)
            continue;

        TerminateProcess(
            child,
            1);

        CloseHandle(
            child);

        previousSamples.remove(
            childPid);

        pathCache.remove(
            childPid);
    }

    // Finally terminate the root process.
    rootTerminated =
        terminateProcess(
            processId);

    return rootTerminated;
}

// =============================================================
// OPEN PROCESS LOCATION
// =============================================================

bool Processes::openProcessLocation(
    const QString& path)
{
    if (path.isEmpty())
        return false;

    const std::wstring widePath =
        path.toStdWString();

    const std::wstring parameters =
        L"/select,\""
        + widePath
        + L"\"";

    const HINSTANCE result =
        ShellExecuteW(
            nullptr,
            L"open",
            L"explorer.exe",
            parameters.c_str(),
            nullptr,
            SW_SHOWNORMAL);

    return
        reinterpret_cast<INT_PTR>(
            result) > 32;
}