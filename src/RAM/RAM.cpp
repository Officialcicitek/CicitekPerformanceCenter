#include "RAM.h"
#include <windows.h>

namespace RAM
{
    MEMORYSTATUSEX GetMemoryStatus()
    {
        MEMORYSTATUSEX memoryStatus{};
        memoryStatus.dwLength = sizeof(memoryStatus);

        GlobalMemoryStatusEx(&memoryStatus);

        return memoryStatus;
    }

    double GetTotalGB()
    {
        auto memoryStatus = GetMemoryStatus();

        return static_cast<double>(memoryStatus.ullTotalPhys)
            / (1024.0 * 1024.0 * 1024.0);
    }

    double GetUsedGB()
    {
        auto memoryStatus = GetMemoryStatus();

        double totalGB =
            static_cast<double>(memoryStatus.ullTotalPhys)
            / (1024.0 * 1024.0 * 1024.0);

        double availableGB =
            static_cast<double>(memoryStatus.ullAvailPhys)
            / (1024.0 * 1024.0 * 1024.0);

        return totalGB - availableGB;
    }

    double GetUsagePercent()
    {
        auto memoryStatus = GetMemoryStatus();

        return static_cast<double>(memoryStatus.dwMemoryLoad);
    }
}