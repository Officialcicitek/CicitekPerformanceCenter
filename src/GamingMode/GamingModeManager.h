#pragma once

#include <windows.h>
#include <QString>

class GamingModeManager
{
public:
    bool enable();
    bool disable();
    bool isEnabled() const;

    QString getActivePowerPlanName() const;

    bool setGameProcessHighPriority(DWORD processId);

    bool resetGameProcessPriority(
        DWORD processId,
        DWORD originalPriority
    );

private:
    bool m_enabled = false;

    GUID m_previousPowerScheme{};
    bool m_hasPreviousPowerScheme = false;
};