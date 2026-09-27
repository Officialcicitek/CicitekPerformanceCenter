#pragma once

#include <windows.h>
#include <QHash>
#include <QString>

class BackgroundOptimizationManager
{
public:
    bool enable();
    bool disable();
    bool isEnabled() const;

private:
    bool m_enabled = false;

    QHash<DWORD, DWORD> m_modifiedProcesses;

    bool optimizeProcess(
        DWORD processId
    );
};