#pragma once

namespace Temperature
{
    double GetCPUTemperature();
    double GetGPUTemperature();
    double GetGPUHotspot();

    double GetGPUUsage();

    double GetGPUVRAMUsed();
    double GetGPUVRAMTotal();
}