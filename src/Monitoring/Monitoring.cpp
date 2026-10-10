
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

        auto measure = [](const char* name, auto function)
        {
            QElapsedTimer timer;
            timer.start();

            auto result = function();

            qDebug().noquote()
                << "[Timing]" << name << timer.elapsed() << "ms";

            return result;
        };

        stats.cpuUsage = measure("CPU usage", [] {
            return CPU::GetUsage();
        });

        stats.cpuTemperature = measure("CPU temperature", [] {
            return Temperature::GetCPUTemperature();
        });

        stats.gpuUsage = measure("GPU usage", [] {
            return Temperature::GetGPUUsage();
        });

        stats.gpuTemperature = measure("GPU temperature", [] {
            return Temperature::GetGPUTemperature();
        });

        stats.gpuHotspot = measure("GPU hotspot", [] {
            return Temperature::GetGPUHotspot();
        });

        stats.gpuVramUsedGB = measure("GPU VRAM used", [] {
            return Temperature::GetGPUVRAMUsed();
        });

        stats.gpuVramTotalGB = measure("GPU VRAM total", [] {
            return Temperature::GetGPUVRAMTotal();
        });

        stats.ramUsedGB = measure("RAM used", [] {
            return RAM::GetUsedGB();
        });

        stats.ramTotalGB = measure("RAM total", [] {
            return RAM::GetTotalGB();
        });

        stats.ramUsagePercent = measure("RAM usage percent", [] {
            return RAM::GetUsagePercent();
        });

        Disk::DiskUsage disk = measure("Disk update", [] {
            return Disk::Update();
        });

        stats.diskReadMBps = disk.readMBps;
        stats.diskWriteMBps = disk.writeMBps;

        Network::NetworkUsage network = measure("Network update", [] {
            return Network::Update();
        });

        stats.networkDownloadMBps = network.downloadMBps;
        stats.networkUploadMBps = network.uploadMBps;

        stats.uptimeSeconds = measure("System uptime", [] {
            return System::GetUptimeSeconds();
        });

        qDebug() << "[Timing] Monitoring finished";

        return stats;
    }
}
