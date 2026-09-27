#include "BackgroundOptimizationManager.h"

#include <tlhelp32.h>

namespace
{
    bool isBackgroundProcess(const QString& processName)
    {
        return
            processName.compare("Discord.exe", Qt::CaseInsensitive) == 0 ||
            processName.compare("Spotify.exe", Qt::CaseInsensitive) == 0 ||
            processName.compare("OneDrive.exe", Qt::CaseInsensitive) == 0 ||
            processName.compare("msedge.exe", Qt::CaseInsensitive) == 0 ||
            processName.compare("chrome.exe", Qt::CaseInsensitive) == 0;
    }
}

bool BackgroundOptimizationManager::enable()
{
    if (m_enabled)
        return true;

    HANDLE snapshot =
        CreateToolhelp32Snapshot(
            TH32CS_SNAPPROCESS,
            0
        );

    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32W processEntry{};
    processEntry.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(snapshot, &processEntry))
    {
        CloseHandle(snapshot);
        return false;
    }

    do
    {
        QString processName =
            QString::fromWCharArray(
                processEntry.szExeFile
            );

        if (!isBackgroundProcess(processName))
            continue;

        optimizeProcess(
            processEntry.th32ProcessID
        );

    } while (Process32NextW(snapshot, &processEntry));

    CloseHandle(snapshot);

    m_enabled = true;

    return true;
}

bool BackgroundOptimizationManager::disable()
{
    if (!m_enabled)
        return true;

    for (auto it = m_modifiedProcesses.constBegin();
         it != m_modifiedProcesses.constEnd();
         ++it)
    {
        DWORD processId = it.key();
        DWORD originalPriority = it.value();

        HANDLE processHandle =
            OpenProcess(
                PROCESS_SET_INFORMATION,
                FALSE,
                processId
            );

        if (processHandle == nullptr)
            continue;

        SetPriorityClass(
            processHandle,
            originalPriority
        );

        CloseHandle(processHandle);
    }

    m_modifiedProcesses.clear();
    m_enabled = false;

    return true;
}

bool BackgroundOptimizationManager::isEnabled() const
{
    return m_enabled;
}

bool BackgroundOptimizationManager::optimizeProcess(
    DWORD processId
)
{
    HANDLE processHandle =
        OpenProcess(
            PROCESS_QUERY_INFORMATION |
            PROCESS_SET_INFORMATION,
            FALSE,
            processId
        );

    if (processHandle == nullptr)
        return false;

    DWORD originalPriority =
        GetPriorityClass(processHandle);

    if (originalPriority == 0)
    {
        CloseHandle(processHandle);
        return false;
    }

    if (
        originalPriority == BELOW_NORMAL_PRIORITY_CLASS ||
        originalPriority == IDLE_PRIORITY_CLASS
    )
    {
        CloseHandle(processHandle);
        return true;
    }

    m_modifiedProcesses.insert(
        processId,
        originalPriority
    );

    BOOL result =
        SetPriorityClass(
            processHandle,
            BELOW_NORMAL_PRIORITY_CLASS
        );

    CloseHandle(processHandle);

    if (!result)
    {
        m_modifiedProcesses.remove(processId);
        return false;
    }

    return true;
}