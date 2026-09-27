#pragma once

#include <QWidget>

#include "../../Monitoring/Monitoring.h"

class QLabel;
class QProgressBar;
class LiveGraph;

class Dashboard : public QWidget
{
public:
    explicit Dashboard(QWidget* parent = nullptr);

    void setLightMode(bool lightMode);

private:
    bool m_lightMode = false;

    // CPU
    QLabel* cpuUsageLabel = nullptr;
    QLabel* cpuTemperatureLabel = nullptr;
    QProgressBar* cpuProgressBar = nullptr;
    LiveGraph* cpuGraph = nullptr;
    LiveGraph* cpuTemperatureGraph = nullptr;

    // GPU
    QLabel* gpuUsageLabel = nullptr;
    QLabel* gpuTemperatureLabel = nullptr;
    QLabel* gpuHotspotLabel = nullptr;
    QLabel* gpuNameLabel = nullptr;
    QLabel* gpuVramLabel = nullptr;
    QProgressBar* gpuProgressBar = nullptr;
    LiveGraph* gpuGraph = nullptr;
    LiveGraph* gpuHotspotGraph = nullptr;
    LiveGraph* gpuTemperatureGraph = nullptr;

    // RAM
    QLabel* ramUsageLabel = nullptr;
    QLabel* ramPercentageLabel = nullptr;
    QProgressBar* ramProgressBar = nullptr;
    LiveGraph* ramGraph = nullptr;

    // STORAGE
    QLabel* diskReadLabel = nullptr;
    QLabel* diskWriteLabel = nullptr;

    // NETWORK
    QLabel* networkDownloadLabel = nullptr;
    QLabel* networkUploadLabel = nullptr;

    // SYSTEM
    QLabel* cpuNameLabel = nullptr;
    QLabel* uptimeLabel = nullptr;

    void updateStats();
};