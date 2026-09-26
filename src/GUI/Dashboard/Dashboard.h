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

private:
    // =========================
    // CPU
    // =========================

    QLabel* cpuUsageLabel;
    QLabel* cpuTemperatureLabel;

    QProgressBar* cpuProgressBar;

    LiveGraph* cpuGraph;
    LiveGraph* cpuTemperatureGraph;


    // =========================
    // GPU
    // =========================

    QLabel* gpuUsageLabel;
    QLabel* gpuTemperatureLabel;
    QLabel* gpuNameLabel;
    QLabel* gpuVramLabel;

    QProgressBar* gpuProgressBar;

    LiveGraph* gpuGraph;
    LiveGraph* gpuTemperatureGraph;


    // =========================
    // RAM
    // =========================

    QLabel* ramUsageLabel;
    QLabel* ramPercentageLabel;

    QProgressBar* ramProgressBar;

    LiveGraph* ramGraph;


    // =========================
    // DISK
    // =========================

    QLabel* diskReadLabel;
    QLabel* diskWriteLabel;


    // =========================
    // NETWORK
    // =========================

    QLabel* networkDownloadLabel;
    QLabel* networkUploadLabel;


    // =========================
    // SYSTEM
    // =========================

    QLabel* uptimeLabel;


    // =========================
    // UPDATE
    // =========================

    void updateStats();
};