#pragma once

namespace Monitoring
{
    struct SystemStats
    {
        // =========================
        // CPU
        // =========================

        double cpuUsage = 0.0;
        double cpuTemperature = -1.0;


        // =========================
        // GPU
        // =========================

        double gpuUsage = -1.0;
        double gpuTemperature = -1.0;
        double gpuHotspot = -1.0;

        double gpuVramUsedGB = -1.0;
        double gpuVramTotalGB = -1.0;


        // =========================
        // RAM
        // =========================

        double ramUsedGB = 0.0;
        double ramTotalGB = 0.0;
        double ramUsagePercent = 0.0;


        // =========================
        // DISK
        // =========================

        double diskReadMBps = 0.0;
        double diskWriteMBps = 0.0;


        // =========================
        // NETWORK
        // =========================

        double networkDownloadMBps = 0.0;
        double networkUploadMBps = 0.0;


        // =========================
        // SYSTEM
        // =========================

        unsigned long long uptimeSeconds = 0;
    };


    void Initialize();

    SystemStats Update();
}