#include "Processes.h"

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

QList<ProcessInfo> Processes::getProcesses()
{
    QList<ProcessInfo> processes;

    HANDLE snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,
        0
    );

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        return processes;
    }

    PROCESSENTRY32W entry{};
    entry.dwSize = sizeof(PROCESSENTRY32W);

    if (Process32FirstW(snapshot, &entry))
    {
        do
        {
            ProcessInfo info;

            info.name = QString::fromWCharArray(entry.szExeFile);
            info.processId = entry.th32ProcessID;
            info.memoryUsage = 0;

            HANDLE process = OpenProcess(
                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                FALSE,
                entry.th32ProcessID
            );

            if (process)
            {
                PROCESS_MEMORY_COUNTERS memoryCounters{};

                if (GetProcessMemoryInfo(
                    process,
                    &memoryCounters,
                    sizeof(memoryCounters)
                ))
                {
                    info.memoryUsage =
                        static_cast<unsigned long long>(
                            memoryCounters.WorkingSetSize
                        );
                }

                CloseHandle(process);
            }

            processes.append(info);

        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);

    return processes;
}