#include "Monitoring.h"

#include "../CPU/CPU.h"
#include "../RAM/RAM.h"
#include "../Disk/Disk.h"
#include "../Network/Network.h"
#include "../System/System.h"
#include "../Temperature/Temperature.h"


namespace Monitoring
{
    void Initialize()
    {
        CPU::Initialize();

        Disk::Initialize();

        Network::Initialize();
    }


    SystemStats Update()
    {
        SystemStats stats;


        // =========================
        // CPU
        // =========================

        stats.cpuUsage =
            CPU::GetUsage();

        stats.cpuTemperature =
            Temperature::GetCPUTemperature();


        // =========================
        // GPU
        // =========================

        stats.gpuUsage =
            Temperature::GetGPUUsage();

        stats.gpuTemperature =
            Temperature::GetGPUTemperature();

        stats.gpuVramUsedGB =
            Temperature::GetGPUVRAMUsed();


        // =========================
        // RAM
        // =========================

        stats.ramUsedGB =
            RAM::GetUsedGB();

        stats.ramTotalGB =
            RAM::GetTotalGB();

        stats.ramUsagePercent =
            RAM::GetUsagePercent();


        // =========================
        // DISK
        // =========================

        Disk::DiskUsage disk =
            Disk::Update();

        stats.diskReadMBps =
            disk.readMBps;

        stats.diskWriteMBps =
            disk.writeMBps;


        // =========================
        // NETWORK
        // =========================

        Network::NetworkUsage network =
            Network::Update();

        stats.networkDownloadMBps =
            network.downloadMBps;

        stats.networkUploadMBps =
            network.uploadMBps;


        // =========================
        // SYSTEM
        // =========================

        stats.uptimeSeconds =
            System::GetUptimeSeconds();


        return stats;
    }
}