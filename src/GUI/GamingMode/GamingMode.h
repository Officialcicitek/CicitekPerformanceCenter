#pragma once

#include <QWidget>
#include <QTimer>
#include <QStringList>
#include <QHash>

#include "../../GamingMode/GamingModeManager.h"
#include "../../GamingMode/BackgroundOptimizationManager.h"

class QLabel;
class QFrame;
class QPushButton;

class GamingMode : public QWidget
{
public:
    explicit GamingMode(QWidget* parent = nullptr);

    void setLightMode(bool lightMode);

private:
    bool m_lightMode = false;

    bool m_autoGamingModeEnabled = true;
    bool m_automaticGamingMode = false;
    bool m_highCpuPriorityEnabled = false;
    bool m_backgroundOptimizationEnabled = false;

    GamingModeManager m_gamingModeManager;
    BackgroundOptimizationManager m_backgroundOptimizationManager;

    QHash<DWORD, DWORD> m_modifiedGameProcesses;

    QFrame* createCard(
        const QString& objectName,
        const QString& title,
        const QString& description
    );

    void applyTheme();

    void detectRunningGame();

    void updateAutomaticGamingMode(
        bool gameDetected
    );

    void restoreModifiedGamePriorities();

    QTimer* gameDetectionTimer = nullptr;

    QLabel* modeStatusLabel = nullptr;
    QLabel* detectedGameLabel = nullptr;
    QLabel* performanceProfileLabel = nullptr;
    QLabel* cpuPriorityStatusLabel = nullptr;
    QLabel* backgroundOptimizationStatusLabel = nullptr;

    QPushButton* modeToggleButton = nullptr;
    QPushButton* autoGamingModeButton = nullptr;
    QPushButton* cpuPriorityButton = nullptr;
    QPushButton* backgroundOptimizationButton = nullptr;
};