#include "Monitoring.h"

#include "../CPU/CPU.h"
#include "../RAM/RAM.h"
#include "../Disk/Disk.h"
#include "../Network/Network.h"
#include "../System/System.h"
#include "../Temperature/Temperature.h"

#include <QDebug>
#include <QElapsedTimer>


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

        QElapsedTimer timer;
        timer.start();


        // =========================
        // CPU
        // =========================

        stats.cpuUsage =
            CPU::GetUsage();

        qDebug()
            << "[Monitoring] CPU usage:"
            << timer.elapsed()
            << "ms";


        stats.cpuTemperature =
            Temperature::GetCPUTemperature();

        qDebug()
            << "[Monitoring] CPU temperature:"
            << timer.elapsed()
            << "ms";


        // =========================
        // GPU
        // =========================

        stats.gpuUsage =
            Temperature::GetGPUUsage();

        qDebug()
            << "[Monitoring] GPU usage:"
            << timer.elapsed()
            << "ms";


        stats.gpuTemperature =
            Temperature::GetGPUTemperature();

        qDebug()
            << "[Monitoring] GPU temperature:"
            << timer.elapsed()
            << "ms";


        stats.gpuHotspot =
            Temperature::GetGPUHotspot();

        qDebug()
            << "[Monitoring] GPU hotspot:"
            << timer.elapsed()
            << "ms";


        stats.gpuVramUsedGB =
            Temperature::GetGPUVRAMUsed();

        qDebug()
            << "[Monitoring] GPU VRAM used:"
            << timer.elapsed()
            << "ms";


        stats.gpuVramTotalGB =
            Temperature::GetGPUVRAMTotal();

        qDebug()
            << "[Monitoring] GPU VRAM total:"
            << timer.elapsed()
            << "ms";


        // =========================
        // RAM
        // =========================

        stats.ramUsedGB =
            RAM::GetUsedGB();

        stats.ramTotalGB =
            RAM::GetTotalGB();

        stats.ramUsagePercent =
            RAM::GetUsagePercent();

        qDebug()
            << "[Monitoring] RAM:"
            << timer.elapsed()
            << "ms";


        // =========================
        // DISK
        // =========================

        Disk::DiskUsage disk =
            Disk::Update();

        stats.diskReadMBps =
            disk.readMBps;

        stats.diskWriteMBps =
            disk.writeMBps;

        qDebug()
            << "[Monitoring] Disk:"
            << timer.elapsed()
            << "ms";


        // =========================
        // NETWORK
        // =========================

        Network::NetworkUsage network =
            Network::Update();

        stats.networkDownloadMBps =
            network.downloadMBps;

        stats.networkUploadMBps =
            network.uploadMBps;

        qDebug()
            << "[Monitoring] Network:"
            << timer.elapsed()
            << "ms";


        // =========================
        // SYSTEM
        // =========================

        stats.uptimeSeconds =
            System::GetUptimeSeconds();

        qDebug()
            << "[Monitoring] System:"
            << timer.elapsed()
            << "ms";


        qDebug()
            << "[Monitoring] TOTAL:"
            << timer.elapsed()
            << "ms";


        return stats;
    }
}