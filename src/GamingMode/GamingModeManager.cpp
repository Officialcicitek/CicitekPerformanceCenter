#include "GamingModeManager.h"

#include <powrprof.h>
#include <windows.h>

#pragma comment(lib, "PowrProf.lib")

bool GamingModeManager::enable()
{
    if (m_enabled)
        return true;

    GUID* activeScheme = nullptr;

    if (
        PowerGetActiveScheme(
            nullptr,
            &activeScheme
        ) != ERROR_SUCCESS
    )
    {
        return false;
    }

    m_previousPowerScheme = *activeScheme;
    m_hasPreviousPowerScheme = true;

    LocalFree(activeScheme);

    const GUID gamingScheme =
    {
        0x8c5e7fda,
        0xe8bf,
        0x4a96,
        {
            0x9a,
            0x85,
            0xa6,
            0xe2,
            0x3a,
            0x8c,
            0x63,
            0x5c
        }
    };

    if (
        PowerSetActiveScheme(
            nullptr,
            &gamingScheme
        ) != ERROR_SUCCESS
    )
    {
        m_hasPreviousPowerScheme = false;
        return false;
    }

    m_enabled = true;

    return true;
}

bool GamingModeManager::disable()
{
    if (!m_enabled)
        return true;

    if (m_hasPreviousPowerScheme)
    {
        if (
            PowerSetActiveScheme(
                nullptr,
                &m_previousPowerScheme
            ) != ERROR_SUCCESS
        )
        {
            return false;
        }
    }

    m_hasPreviousPowerScheme = false;
    m_enabled = false;

    return true;
}

bool GamingModeManager::isEnabled() const
{
    return m_enabled;
}

QString GamingModeManager::getActivePowerPlanName() const
{
    GUID* activeScheme = nullptr;

    if (
        PowerGetActiveScheme(
            nullptr,
            &activeScheme
        ) != ERROR_SUCCESS
    )
    {
        return "Unknown";
    }

    wchar_t buffer[256] = {};

    DWORD bufferSize =
        sizeof(buffer);

    DWORD result =
        PowerReadFriendlyName(
            nullptr,
            activeScheme,
            nullptr,
            nullptr,
            reinterpret_cast<PUCHAR>(
                buffer
            ),
            &bufferSize
        );

    LocalFree(activeScheme);

    if (result != ERROR_SUCCESS)
        return "Unknown";

    return QString::fromWCharArray(
        buffer
    );
}

bool GamingModeManager::setGameProcessHighPriority(
    DWORD processId
)
{
    HANDLE processHandle =
        OpenProcess(
            PROCESS_SET_INFORMATION,
            FALSE,
            processId
        );

    if (processHandle == nullptr)
        return false;

    BOOL result =
        SetPriorityClass(
            processHandle,
            HIGH_PRIORITY_CLASS
        );

    CloseHandle(processHandle);

    return result != FALSE;
}

bool GamingModeManager::resetGameProcessPriority(
    DWORD processId,
    DWORD originalPriority
)
{
    HANDLE processHandle =
        OpenProcess(
            PROCESS_SET_INFORMATION,
            FALSE,
            processId
        );

    if (processHandle == nullptr)
        return false;

    BOOL result =
        SetPriorityClass(
            processHandle,
            originalPriority
        );

    CloseHandle(processHandle);

    return result != FALSE;
}