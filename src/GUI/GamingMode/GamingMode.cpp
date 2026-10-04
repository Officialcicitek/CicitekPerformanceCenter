#include "GamingMode.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QSizePolicy>
#include <QStyle>
#include <QTimer>
#include <QVBoxLayout>

#include <windows.h>
#include <tlhelp32.h>

// =============================================================
// CONSTRUCTOR
// =============================================================

GamingMode::GamingMode(QWidget* parent)
    : QWidget(parent)
{
    setObjectName("gamingModePage");

    // =========================================================
    // LOAD SAVED SETTINGS
    // =========================================================

    loadSettings();

    // =========================================================
    // MAIN LAYOUT
    // =========================================================

    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        30,
        25,
        30,
        30
    );

    mainLayout->setSpacing(20);

    // =========================================================
    // HEADER
    // =========================================================

    QLabel* titleLabel =
        new QLabel("Gaming Mode");

    titleLabel->setObjectName("pageTitle");

    QLabel* subtitleLabel =
        new QLabel(
            "Optimize your PC for gaming performance."
        );

    subtitleLabel->setObjectName("pageSubtitle");

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(subtitleLabel);

    // =========================================================
    // GAMING MODE CARD
    // =========================================================

    QFrame* modeCard =
        createCard(
            "gamingModeCard",
            "GAMING MODE",
            "Enable performance-focused settings for gaming."
        );

    QVBoxLayout* modeLayout =
        qobject_cast<QVBoxLayout*>(
            modeCard->layout()
        );

    QHBoxLayout* modeStatusLayout =
        new QHBoxLayout();

    modeStatusLayout->setContentsMargins(
        0,
        8,
        0,
        0
    );

    modeStatusLabel =
        new QLabel(
            "Gaming Mode is OFF"
        );

    modeStatusLabel->setObjectName(
        "modeStatusLabel"
    );

    autoGamingModeButton =
        new QPushButton();

    autoGamingModeButton->setObjectName(
        "autoToggleButton"
    );

    autoGamingModeButton->setCursor(
        Qt::PointingHandCursor
    );

    autoGamingModeButton->setSizePolicy(
        QSizePolicy::Fixed,
        QSizePolicy::Fixed
    );

    autoGamingModeButton->setProperty(
        "active",
        m_autoGamingModeEnabled
    );

    autoGamingModeButton->setText(
        m_autoGamingModeEnabled
            ? "AUTO ON"
            : "AUTO OFF"
    );

    modeStatusLayout->addWidget(
        modeStatusLabel
    );

    modeStatusLayout->addStretch();

    modeStatusLayout->addWidget(
        autoGamingModeButton
    );

    modeLayout->addLayout(
        modeStatusLayout
    );

    modeToggleButton =
        new QPushButton(
            "ENABLE"
        );

    modeToggleButton->setObjectName(
        "gamingToggleButton"
    );

    modeToggleButton->setCursor(
        Qt::PointingHandCursor
    );

    modeToggleButton->setProperty(
        "active",
        false
    );

    modeLayout->addSpacing(10);

    modeLayout->addWidget(
        modeToggleButton
    );

    mainLayout->addWidget(
        modeCard
    );

    // =========================================================
    // LOWER GRID
    // =========================================================

    QGridLayout* cardsGrid =
        new QGridLayout();

    cardsGrid->setContentsMargins(
        0,
        0,
        0,
        0
    );

    cardsGrid->setHorizontalSpacing(15);
    cardsGrid->setVerticalSpacing(15);

    // =========================================================
    // HIGH CPU PRIORITY
    // =========================================================

    QFrame* cpuCard =
        createCard(
            "statusCard",
            "HIGH CPU PRIORITY",
            "Give supported detected games higher process priority."
        );

    QVBoxLayout* cpuCardLayout =
        qobject_cast<QVBoxLayout*>(
            cpuCard->layout()
        );

    cpuPriorityStatusLabel =
        new QLabel(
            "Boost game process priority"
        );

    cpuPriorityStatusLabel->setObjectName(
        "cpuPriorityStatusLabel"
    );

    cpuPriorityStatusLabel->setWordWrap(
        true
    );

    cpuPriorityButton =
        new QPushButton(
            m_highCpuPriorityEnabled
                ? "ON"
                : "OFF"
        );

    cpuPriorityButton->setObjectName(
        "settingToggleButton"
    );

    cpuPriorityButton->setCursor(
        Qt::PointingHandCursor
    );

    cpuPriorityButton->setSizePolicy(
        QSizePolicy::Fixed,
        QSizePolicy::Fixed
    );

    cpuPriorityButton->setProperty(
        "active",
        m_highCpuPriorityEnabled
    );

    cpuCardLayout->addStretch();

    cpuCardLayout->addWidget(
        cpuPriorityStatusLabel
    );

    QHBoxLayout* cpuButtonLayout =
        new QHBoxLayout();

    cpuButtonLayout->setContentsMargins(
        0,
        8,
        0,
        0
    );

    cpuButtonLayout->addStretch();

    cpuButtonLayout->addWidget(
        cpuPriorityButton
    );

    cpuCardLayout->addLayout(
        cpuButtonLayout
    );

    cardsGrid->addWidget(
        cpuCard,
        0,
        0
    );

    // =========================================================
    // GAME DETECTION
    // =========================================================

    QFrame* gameCard =
        createCard(
            "statusCard",
            "GAME DETECTION",
            "Currently detected games."
        );

    QVBoxLayout* gameLayout =
        qobject_cast<QVBoxLayout*>(
            gameCard->layout()
        );

    detectedGameLabel =
        new QLabel(
            "No game detected"
        );

    detectedGameLabel->setObjectName(
        "statusValue"
    );

    detectedGameLabel->setWordWrap(
        true
    );

    gameLayout->addStretch();

    gameLayout->addWidget(
        detectedGameLabel
    );

    cardsGrid->addWidget(
        gameCard,
        0,
        1
    );

    // =========================================================
    // BACKGROUND OPTIMIZATION
    // =========================================================

    QFrame* backgroundCard =
        createCard(
            "statusCard",
            "BACKGROUND OPTIMIZATION",
            "Lower priority of selected background applications."
        );

    QVBoxLayout* backgroundLayout =
        qobject_cast<QVBoxLayout*>(
            backgroundCard->layout()
        );

    backgroundOptimizationStatusLabel =
        new QLabel(
            m_backgroundOptimizationEnabled
                ? "Ready • activates with Gaming Mode"
                : "Optimization is disabled"
        );

    backgroundOptimizationStatusLabel->setObjectName(
        "cpuPriorityStatusLabel"
    );

    backgroundOptimizationStatusLabel->setWordWrap(
        true
    );

    backgroundOptimizationButton =
        new QPushButton(
            m_backgroundOptimizationEnabled
                ? "ON"
                : "OFF"
        );

    backgroundOptimizationButton->setObjectName(
        "settingToggleButton"
    );

    backgroundOptimizationButton->setCursor(
        Qt::PointingHandCursor
    );

    backgroundOptimizationButton->setSizePolicy(
        QSizePolicy::Fixed,
        QSizePolicy::Fixed
    );

    backgroundOptimizationButton->setProperty(
        "active",
        m_backgroundOptimizationEnabled
    );

    backgroundLayout->addStretch();

    backgroundLayout->addWidget(
        backgroundOptimizationStatusLabel
    );

    QHBoxLayout* backgroundButtonLayout =
        new QHBoxLayout();

    backgroundButtonLayout->setContentsMargins(
        0,
        8,
        0,
        0
    );

    backgroundButtonLayout->addStretch();

    backgroundButtonLayout->addWidget(
        backgroundOptimizationButton
    );

    backgroundLayout->addLayout(
        backgroundButtonLayout
    );

    cardsGrid->addWidget(
        backgroundCard,
        1,
        0
    );

    // =========================================================
    // PERFORMANCE PROFILE
    // =========================================================

    QFrame* performanceCard =
        createCard(
            "statusCard",
            "PERFORMANCE PROFILE",
            "Currently active Windows power plan."
        );

    QVBoxLayout* performanceLayout =
        qobject_cast<QVBoxLayout*>(
            performanceCard->layout()
        );

    performanceProfileLabel =
        new QLabel(
            m_gamingModeManager
                .getActivePowerPlanName()
        );

    performanceProfileLabel->setObjectName(
        "statusValue"
    );

    performanceProfileLabel->setWordWrap(
        true
    );

    performanceLayout->addStretch();

    performanceLayout->addWidget(
        performanceProfileLabel
    );

    cardsGrid->addWidget(
        performanceCard,
        1,
        1
    );

    cardsGrid->setColumnStretch(
        0,
        1
    );

    cardsGrid->setColumnStretch(
        1,
        1
    );

    mainLayout->addLayout(
        cardsGrid
    );

    mainLayout->addStretch();

    // =========================================================
    // GAMING MODE TOGGLE
    // =========================================================

    connect(
        modeToggleButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            if (
                !m_gamingModeManager.isEnabled()
            )
            {
                if (
                    m_gamingModeManager.enable()
                )
                {
                    m_automaticGamingMode =
                        false;

                    modeStatusLabel->setText(
                        "Gaming Mode is ON"
                    );

                    modeToggleButton->setText(
                        "DISABLE"
                    );

                    modeToggleButton->setProperty(
                        "active",
                        true
                    );

                    modeToggleButton->style()->unpolish(
                        modeToggleButton
                    );

                    modeToggleButton->style()->polish(
                        modeToggleButton
                    );

                    performanceProfileLabel->setText(
                        m_gamingModeManager
                            .getActivePowerPlanName()
                    );

                    if (
                        m_backgroundOptimizationEnabled
                    )
                    {
                        if (
                            m_backgroundOptimizationManager
                                .enable()
                        )
                        {
                            backgroundOptimizationStatusLabel
                                ->setText(
                                    "Background applications optimized"
                                );
                        }
                        else
                        {
                            backgroundOptimizationStatusLabel
                                ->setText(
                                    "Optimization failed"
                                );
                        }
                    }

                    detectRunningGame();
                }
            }
            else
            {
                if (
                    m_gamingModeManager.disable()
                )
                {
                    m_automaticGamingMode =
                        false;

                    modeStatusLabel->setText(
                        "Gaming Mode is OFF"
                    );

                    modeToggleButton->setText(
                        "ENABLE"
                    );

                    modeToggleButton->setProperty(
                        "active",
                        false
                    );

                    modeToggleButton->style()->unpolish(
                        modeToggleButton
                    );

                    modeToggleButton->style()->polish(
                        modeToggleButton
                    );

                    performanceProfileLabel->setText(
                        m_gamingModeManager
                            .getActivePowerPlanName()
                    );

                    restoreModifiedGamePriorities();

                    m_backgroundOptimizationManager
                        .disable();

                    if (
                        m_backgroundOptimizationEnabled
                    )
                    {
                        backgroundOptimizationStatusLabel
                            ->setText(
                                "Ready • activates with Gaming Mode"
                            );
                    }
                    else
                    {
                        backgroundOptimizationStatusLabel
                            ->setText(
                                "Optimization is disabled"
                            );
                    }
                }
            }
        }
    );

    // =========================================================
    // AUTO GAMING MODE
    // =========================================================

    connect(
        autoGamingModeButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            m_autoGamingModeEnabled =
                !m_autoGamingModeEnabled;

            saveSettings();

            autoGamingModeButton->setText(
                m_autoGamingModeEnabled
                    ? "AUTO ON"
                    : "AUTO OFF"
            );

            autoGamingModeButton->setProperty(
                "active",
                m_autoGamingModeEnabled
            );

            autoGamingModeButton->style()->unpolish(
                autoGamingModeButton
            );

            autoGamingModeButton->style()->polish(
                autoGamingModeButton
            );

            if (
                m_autoGamingModeEnabled
            )
            {
                detectRunningGame();
            }
            else
            {
                if (
                    m_automaticGamingMode &&
                    m_gamingModeManager.isEnabled()
                )
                {
                    if (
                        m_gamingModeManager.disable()
                    )
                    {
                        m_automaticGamingMode =
                            false;

                        modeStatusLabel->setText(
                            "Gaming Mode is OFF"
                        );

                        modeToggleButton->setText(
                            "ENABLE"
                        );

                        modeToggleButton->setProperty(
                            "active",
                            false
                        );

                        modeToggleButton->style()->unpolish(
                            modeToggleButton
                        );

                        modeToggleButton->style()->polish(
                            modeToggleButton
                        );

                        performanceProfileLabel->setText(
                            m_gamingModeManager
                                .getActivePowerPlanName()
                        );

                        restoreModifiedGamePriorities();

                        m_backgroundOptimizationManager
                            .disable();

                        if (
                            m_backgroundOptimizationEnabled
                        )
                        {
                            backgroundOptimizationStatusLabel
                                ->setText(
                                    "Ready • activates with Gaming Mode"
                                );
                        }
                    }
                }
            }
        }
    );

    // =========================================================
    // HIGH CPU PRIORITY
    // =========================================================

    connect(
        cpuPriorityButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            m_highCpuPriorityEnabled =
                !m_highCpuPriorityEnabled;

            saveSettings();

            cpuPriorityButton->setText(
                m_highCpuPriorityEnabled
                    ? "ON"
                    : "OFF"
            );

            cpuPriorityButton->setProperty(
                "active",
                m_highCpuPriorityEnabled
            );

            cpuPriorityButton->style()->unpolish(
                cpuPriorityButton
            );

            cpuPriorityButton->style()->polish(
                cpuPriorityButton
            );

            if (
                m_highCpuPriorityEnabled
            )
            {
                if (
                    m_gamingModeManager.isEnabled()
                )
                {
                    cpuPriorityStatusLabel->setText(
                        "Ready to boost supported detected game"
                    );

                    detectRunningGame();
                }
                else
                {
                    cpuPriorityStatusLabel->setText(
                        "Gaming Mode is OFF"
                    );
                }
            }
            else
            {
                restoreModifiedGamePriorities();

                if (
                    m_gamingModeManager.isEnabled()
                )
                {
                    cpuPriorityStatusLabel->setText(
                        "Ready to boost supported detected game"
                    );
                }
                else
                {
                    cpuPriorityStatusLabel->setText(
                        "Gaming Mode is OFF"
                    );
                }
            }
        }
    );

    // =========================================================
    // BACKGROUND OPTIMIZATION
    // =========================================================

    connect(
        backgroundOptimizationButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            m_backgroundOptimizationEnabled =
                !m_backgroundOptimizationEnabled;

            saveSettings();

            backgroundOptimizationButton->setText(
                m_backgroundOptimizationEnabled
                    ? "ON"
                    : "OFF"
            );

            backgroundOptimizationButton->setProperty(
                "active",
                m_backgroundOptimizationEnabled
            );

            backgroundOptimizationButton->style()->unpolish(
                backgroundOptimizationButton
            );

            backgroundOptimizationButton->style()->polish(
                backgroundOptimizationButton
            );

            if (
                m_backgroundOptimizationEnabled
            )
            {
                if (
                    m_gamingModeManager.isEnabled()
                )
                {
                    if (
                        m_backgroundOptimizationManager
                            .enable()
                    )
                    {
                        backgroundOptimizationStatusLabel
                            ->setText(
                                "Background applications optimized"
                            );
                    }
                    else
                    {
                        backgroundOptimizationStatusLabel
                            ->setText(
                                "Optimization failed"
                            );
                    }
                }
                else
                {
                    backgroundOptimizationStatusLabel
                        ->setText(
                            "Ready • activates with Gaming Mode"
                        );
                }
            }
            else
            {
                m_backgroundOptimizationManager
                    .disable();

                backgroundOptimizationStatusLabel
                    ->setText(
                        "Optimization is disabled"
                    );
            }
        }
    );

    // =========================================================
    // GAME DETECTION TIMER
    // =========================================================

    gameDetectionTimer =
        new QTimer(this);

    connect(
        gameDetectionTimer,
        &QTimer::timeout,
        this,
        &GamingMode::detectRunningGame
    );

    gameDetectionTimer->start(
        1000
    );

    detectRunningGame();

    // =========================================================
    // THEME
    // =========================================================

    applyTheme();
}

// =============================================================
// LOAD SETTINGS
// =============================================================

void GamingMode::loadSettings()
{
    m_autoGamingModeEnabled =
        m_settingsManager.value(
            "GamingMode/AutoGamingMode",
            true
        ).toBool();

    m_highCpuPriorityEnabled =
        m_settingsManager.value(
            "GamingMode/HighCpuPriority",
            false
        ).toBool();

    m_backgroundOptimizationEnabled =
        m_settingsManager.value(
            "GamingMode/BackgroundOptimization",
            false
        ).toBool();
}

// =============================================================
// SAVE SETTINGS
// =============================================================

void GamingMode::saveSettings()
{
    m_settingsManager.setValue(
        "GamingMode/AutoGamingMode",
        m_autoGamingModeEnabled
    );

    m_settingsManager.setValue(
        "GamingMode/HighCpuPriority",
        m_highCpuPriorityEnabled
    );

    m_settingsManager.setValue(
        "GamingMode/BackgroundOptimization",
        m_backgroundOptimizationEnabled
    );
}

// =============================================================
// CREATE CARD
// =============================================================

QFrame* GamingMode::createCard(
    const QString& objectName,
    const QString& title,
    const QString& description
)
{
    QFrame* card =
        new QFrame();

    card->setObjectName(
        objectName
    );

    QVBoxLayout* layout =
        new QVBoxLayout(card);

    layout->setContentsMargins(
        20,
        18,
        20,
        18
    );

    layout->setSpacing(
        8
    );

    QLabel* titleLabel =
        new QLabel(title);

    titleLabel->setObjectName(
        "cardTitle"
    );

    QLabel* descriptionLabel =
        new QLabel(description);

    descriptionLabel->setObjectName(
        "cardDescription"
    );

    descriptionLabel->setWordWrap(
        true
    );

    layout->addWidget(
        titleLabel
    );

    layout->addWidget(
        descriptionLabel
    );

    return card;
}

// =============================================================
// RESTORE GAME PRIORITIES
// =============================================================

void GamingMode::restoreModifiedGamePriorities()
{
    for (
        auto it =
            m_modifiedGameProcesses.begin();
        it !=
            m_modifiedGameProcesses.end();
        ++it
    )
    {
        m_gamingModeManager
            .resetGameProcessPriority(
                it.key(),
                it.value()
            );
    }

    m_modifiedGameProcesses.clear();
}

// =============================================================
// GAME DETECTION
// =============================================================

void GamingMode::detectRunningGame()
{
    HANDLE snapshot =
        CreateToolhelp32Snapshot(
            TH32CS_SNAPPROCESS,
            0
        );

    if (
        snapshot ==
        INVALID_HANDLE_VALUE
    )
    {
        detectedGameLabel->setText(
            "Detection unavailable"
        );

        cpuPriorityStatusLabel->setText(
            "Detection unavailable"
        );

        return;
    }

    PROCESSENTRY32W entry{};

    entry.dwSize =
        sizeof(entry);

    QStringList detectedGames;

    QHash<DWORD, QString> currentGameProcesses;

    if (
        Process32FirstW(
            snapshot,
            &entry
        )
    )
    {
        do
        {
            QString processName =
                QString::fromWCharArray(
                    entry.szExeFile
                );

            if (
                !m_gameProfileManager.hasProfile(
                    processName
                )
            )
            {
                continue;
            }

            GameProfile profile =
                m_gameProfileManager.getProfile(
                    processName
                );

            const DWORD processId =
                entry.th32ProcessID;

            detectedGames.append(
                profile.gameName
            );

            currentGameProcesses.insert(
                processId,
                profile.gameName
            );

        }
        while (
            Process32NextW(
                snapshot,
                &entry
            )
        );
    }

    CloseHandle(
        snapshot
    );

    detectedGames.removeDuplicates();

    const bool gameDetected =
        !detectedGames.isEmpty();

    // =========================================================
    // GAME DETECTION DISPLAY
    // =========================================================

    if (
        gameDetected
    )
    {
        detectedGameLabel->setText(
            detectedGames.join(
                "\n"
            )
        );
    }
    else
    {
        detectedGameLabel->setText(
            "No game detected"
        );
    }

    // =========================================================
    // HIGH CPU PRIORITY
    //
    // IMPORTANT:
    // Priority changes are allowed ONLY while Gaming Mode
    // is actually enabled.
    // =========================================================

    QStringList cpuPriorityStatus;

    if (
        m_highCpuPriorityEnabled &&
        m_gamingModeManager.isEnabled()
    )
    {
        for (
            auto it =
                currentGameProcesses.begin();
            it !=
                currentGameProcesses.end();
            ++it
        )
        {
            const DWORD processId =
                it.key();

            const QString gameName =
                it.value();

            HANDLE processHandle =
                OpenProcess(
                    PROCESS_QUERY_INFORMATION,
                    FALSE,
                    processId
                );

            if (
                processHandle == nullptr
            )
            {
                cpuPriorityStatus.append(
                    gameName +
                    " • FAILED"
                );

                continue;
            }

            wchar_t processBuffer[MAX_PATH] = {};

            DWORD bufferSize =
                MAX_PATH;

            if (
                QueryFullProcessImageNameW(
                    processHandle,
                    0,
                    processBuffer,
                    &bufferSize
                )
            )
            {
                QString fullPath =
                    QString::fromWCharArray(
                        processBuffer
                    );

                QString actualProcessName =
                    fullPath.section(
                        '\\',
                        -1
                    );

                if (
                    !m_gameProfileManager.hasProfile(
                        actualProcessName
                    )
                )
                {
                    CloseHandle(
                        processHandle
                    );

                    cpuPriorityStatus.append(
                        gameName +
                        " • PROFILE NOT FOUND"
                    );

                    continue;
                }

                GameProfile profile =
                    m_gameProfileManager.getProfile(
                        actualProcessName
                    );

                if (
                    !profile.highCpuPriority
                )
                {
                    CloseHandle(
                        processHandle
                    );

                    cpuPriorityStatus.append(
                        gameName +
                        " • PROFILE: PRIORITY OFF"
                    );

                    continue;
                }
            }

            DWORD originalPriority =
                GetPriorityClass(
                    processHandle
                );

            CloseHandle(
                processHandle
            );

            if (
                originalPriority == 0
            )
            {
                cpuPriorityStatus.append(
                    gameName +
                    " • FAILED"
                );

                continue;
            }

            if (
                m_modifiedGameProcesses.contains(
                    processId
                )
            )
            {
                cpuPriorityStatus.append(
                    gameName +
                    " • HIGH PRIORITY"
                );

                continue;
            }

            if (
                m_gamingModeManager
                    .setGameProcessHighPriority(
                        processId
                    )
            )
            {
                m_modifiedGameProcesses.insert(
                    processId,
                    originalPriority
                );

                cpuPriorityStatus.append(
                    gameName +
                    " • HIGH PRIORITY"
                );
            }
            else
            {
                cpuPriorityStatus.append(
                    gameName +
                    " • FAILED"
                );
            }
        }

        if (
            cpuPriorityStatus.isEmpty()
        )
        {
            cpuPriorityStatusLabel->setText(
                "No detected game is configured for High CPU Priority"
            );
        }
        else
        {
            cpuPriorityStatusLabel->setText(
                cpuPriorityStatus.join(
                    "\n"
                )
            );
        }
    }
    else
    {
        if (
            !m_gamingModeManager.isEnabled()
        )
        {
            cpuPriorityStatusLabel->setText(
                "Gaming Mode is OFF"
            );
        }
        else if (
            gameDetected
        )
        {
            cpuPriorityStatusLabel->setText(
                "Ready to boost supported detected game"
            );
        }
        else
        {
            cpuPriorityStatusLabel->setText(
                "Boost game process priority"
            );
        }
    }

    // =========================================================
    // BACKGROUND OPTIMIZATION PROFILE
    // =========================================================

    if (
        m_backgroundOptimizationEnabled
    )
    {
        bool backgroundProfileFound =
            false;

        for (
            auto it =
                currentGameProcesses.begin();
            it !=
                currentGameProcesses.end();
            ++it
        )
        {
            HANDLE processHandle =
                OpenProcess(
                    PROCESS_QUERY_LIMITED_INFORMATION,
                    FALSE,
                    it.key()
                );

            if (
                processHandle == nullptr
            )
            {
                continue;
            }

            wchar_t processBuffer[MAX_PATH] = {};

            DWORD bufferSize =
                MAX_PATH;

            if (
                QueryFullProcessImageNameW(
                    processHandle,
                    0,
                    processBuffer,
                    &bufferSize
                )
            )
            {
                QString fullPath =
                    QString::fromWCharArray(
                        processBuffer
                    );

                QString actualProcessName =
                    fullPath.section(
                        '\\',
                        -1
                    );

                if (
                    m_gameProfileManager.hasProfile(
                        actualProcessName
                    )
                )
                {
                    GameProfile profile =
                        m_gameProfileManager.getProfile(
                            actualProcessName
                        );

                    if (
                        profile.backgroundOptimization
                    )
                    {
                        backgroundProfileFound =
                            true;
                    }
                }
            }

            CloseHandle(
                processHandle
            );

            if (
                backgroundProfileFound
            )
            {
                break;
            }
        }

        if (
            backgroundProfileFound
        )
        {
            if (
                m_gamingModeManager.isEnabled()
            )
            {
                if (
                    !m_backgroundOptimizationManager.isEnabled()
                )
                {
                    m_backgroundOptimizationManager
                        .enable();
                }

                backgroundOptimizationStatusLabel
                    ->setText(
                        "Background optimization active"
                    );
            }
            else
            {
                backgroundOptimizationStatusLabel
                    ->setText(
                        "Ready • activates with Gaming Mode"
                    );
            }
        }
        else if (
            gameDetected
        )
        {
            backgroundOptimizationStatusLabel
                ->setText(
                    "Profile does not use background optimization"
                );
        }
        else
        {
            backgroundOptimizationStatusLabel
                ->setText(
                    "Waiting for supported game"
                );
        }
    }
    else
    {
        backgroundOptimizationStatusLabel
            ->setText(
                "Optimization is disabled"
            );
    }

    // =========================================================
    // REMOVE CLOSED GAME PROCESSES
    // =========================================================

    QList<DWORD> processesToRemove;

    for (
        auto it =
            m_modifiedGameProcesses.begin();
        it !=
            m_modifiedGameProcesses.end();
        ++it
    )
    {
        if (
            !currentGameProcesses.contains(
                it.key()
            )
        )
        {
            processesToRemove.append(
                it.key()
            );
        }
    }

    for (
        DWORD processId :
        processesToRemove
    )
    {
        m_modifiedGameProcesses.remove(
            processId
        );
    }

    // =========================================================
    // AUTOMATIC GAMING MODE
    // =========================================================

    updateAutomaticGamingMode(
        gameDetected
    );
}

// =============================================================
// AUTOMATIC GAMING MODE
// =============================================================

void GamingMode::updateAutomaticGamingMode(
    bool gameDetected
)
{
    if (
        !m_autoGamingModeEnabled
    )
    {
        return;
    }

    if (
        gameDetected
    )
    {
        if (
            !m_gamingModeManager.isEnabled()
        )
        {
            if (
                m_gamingModeManager.enable()
            )
            {
                m_automaticGamingMode =
                    true;

                modeStatusLabel->setText(
                    "Gaming Mode is ON • Automatic"
                );

                modeToggleButton->setText(
                    "DISABLE"
                );

                modeToggleButton->setProperty(
                    "active",
                    true
                );

                modeToggleButton->style()->unpolish(
                    modeToggleButton
                );

                modeToggleButton->style()->polish(
                    modeToggleButton
                );

                performanceProfileLabel->setText(
                    m_gamingModeManager
                        .getActivePowerPlanName()
                );

                if (
                    m_backgroundOptimizationEnabled
                )
                {
                    if (
                        m_backgroundOptimizationManager
                            .enable()
                    )
                    {
                        backgroundOptimizationStatusLabel
                            ->setText(
                                "Background applications optimized"
                            );
                    }
                    else
                    {
                        backgroundOptimizationStatusLabel
                            ->setText(
                                "Optimization failed"
                            );
                    }
                }
            }
        }

        return;
    }

    if (
        m_automaticGamingMode &&
        m_gamingModeManager.isEnabled()
    )
    {
        if (
            m_gamingModeManager.disable()
        )
        {
            m_automaticGamingMode =
                false;

            modeStatusLabel->setText(
                "Gaming Mode is OFF"
            );

            modeToggleButton->setText(
                "ENABLE"
            );

            modeToggleButton->setProperty(
                "active",
                false
            );

            modeToggleButton->style()->unpolish(
                modeToggleButton
            );

            modeToggleButton->style()->polish(
                modeToggleButton
            );

            performanceProfileLabel->setText(
                m_gamingModeManager
                    .getActivePowerPlanName()
            );

            restoreModifiedGamePriorities();

            m_backgroundOptimizationManager
                .disable();

            if (
                m_backgroundOptimizationEnabled
            )
            {
                backgroundOptimizationStatusLabel
                    ->setText(
                        "Ready • activates with Gaming Mode"
                    );
            }
            else
            {
                backgroundOptimizationStatusLabel
                    ->setText(
                        "Optimization is disabled"
                    );
            }
        }
    }
}

// =============================================================
// LIGHT MODE
// =============================================================

void GamingMode::setLightMode(
    bool lightMode
)
{
    m_lightMode =
        lightMode;

    applyTheme();
}

// =============================================================
// THEME
// =============================================================

void GamingMode::applyTheme()
{
    if (m_lightMode)
    {
        setStyleSheet(R"(
            #gamingModePage {
                background: #f5f6f8;
            }

            #pageTitle {
                color: #15171a;
                font-size: 28px;
                font-weight: 700;
            }

            #pageSubtitle {
                color: #6b7078;
                font-size: 14px;
            }

            #gamingModeCard,
            #statusCard {
                background: #ffffff;
                border: 1px solid #e1e4e8;
                border-radius: 14px;
            }

            #cardTitle {
                color: #17191c;
                font-size: 12px;
                font-weight: 700;
            }

            #cardDescription {
                color: #777d86;
                font-size: 13px;
            }

            #modeStatusLabel {
                color: #555b63;
                font-size: 15px;
                font-weight: 600;
            }

            #statusValue {
                color: #17191c;
                font-size: 20px;
                font-weight: 700;
            }

            #cpuPriorityStatusLabel {
                color: #68707b;
                font-size: 12px;
                font-weight: 600;
            }

            #gamingToggleButton {
                background: #1677ff;
                color: #ffffff;
                border: 1px solid #1677ff;
                border-radius: 10px;
                padding: 12px 20px;
                font-size: 13px;
                font-weight: 700;
            }

            #gamingToggleButton:hover {
                background: #2b86ff;
                border-color: #2b86ff;
            }

            #gamingToggleButton:pressed {
                background: #0f64d8;
                border-color: #0f64d8;
            }

            #gamingToggleButton[active="false"] {
                background: #707781;
                border-color: #707781;
            }

            #gamingToggleButton[active="false"]:hover {
                background: #7c848e;
                border-color: #7c848e;
            }

            #settingToggleButton {
                background: #edf0f4;
                color: #4b535e;
                border: 1px solid #dce1e7;
                border-radius: 9px;
                padding: 8px 18px;
                font-size: 12px;
                font-weight: 700;
                min-width: 64px;
            }

            #settingToggleButton:hover {
                background: #e3e8ee;
                color: #20252c;
                border-color: #cfd6de;
            }

            #settingToggleButton:pressed {
                background: #d8dee6;
            }

            #settingToggleButton[active="true"] {
                background: #1677ff;
                color: #ffffff;
                border-color: #1677ff;
            }

            #settingToggleButton[active="true"]:hover {
                background: #2b86ff;
                border-color: #2b86ff;
            }

            #settingToggleButton[active="true"]:pressed {
                background: #0f64d8;
                border-color: #0f64d8;
            }

            #autoToggleButton {
                background: #edf0f4;
                color: #4b535e;
                border: 1px solid #dce1e7;
                border-radius: 12px;
                padding: 6px 12px;
                font-size: 11px;
                font-weight: 700;
                min-width: 72px;
            }

            #autoToggleButton:hover {
                background: #e3e8ee;
                border-color: #cfd6de;
            }

            #autoToggleButton:pressed {
                background: #d8dee6;
            }

            #autoToggleButton[active="true"] {
                background: #1677ff;
                color: #ffffff;
                border-color: #1677ff;
            }

            #autoToggleButton[active="true"]:hover {
                background: #2b86ff;
            }

            #autoToggleButton[active="true"]:pressed {
                background: #0f64d8;
            }
        )");
    }
    else
    {
        setStyleSheet(R"(
            #gamingModePage {
                background: #0b0e13;
            }

            #pageTitle {
                color: #f1f3f5;
                font-size: 28px;
                font-weight: 700;
            }

            #pageSubtitle {
                color: #858b96;
                font-size: 14px;
            }

            #gamingModeCard,
            #statusCard {
                background: #11151c;
                border: 1px solid #202630;
                border-radius: 14px;
            }

            #cardTitle {
                color: #e9ebef;
                font-size: 12px;
                font-weight: 700;
            }

            #cardDescription {
                color: #858b96;
                font-size: 13px;
            }

            #modeStatusLabel {
                color: #b4bac4;
                font-size: 15px;
                font-weight: 600;
            }

            #statusValue {
                color: #f0f2f5;
                font-size: 20px;
                font-weight: 700;
            }

            #cpuPriorityStatusLabel {
                color: #9fa7b3;
                font-size: 12px;
                font-weight: 600;
            }

            #gamingToggleButton {
                background: #1677ff;
                color: #ffffff;
                border: 1px solid #1677ff;
                border-radius: 10px;
                padding: 12px 20px;
                font-size: 13px;
                font-weight: 700;
            }

            #gamingToggleButton:hover {
                background: #2b86ff;
                border-color: #2b86ff;
            }

            #gamingToggleButton:pressed {
                background: #0f64d8;
                border-color: #0f64d8;
            }

            #gamingToggleButton[active="false"] {
                background: #5f6670;
                border-color: #5f6670;
            }

            #gamingToggleButton[active="false"]:hover {
                background: #6b737e;
                border-color: #6b737e;
            }

            #settingToggleButton {
                background: #242a33;
                color: #aeb6c2;
                border: 1px solid #343c48;
                border-radius: 9px;
                padding: 8px 18px;
                font-size: 12px;
                font-weight: 700;
                min-width: 64px;
            }

            #settingToggleButton:hover {
                background: #2d3541;
                color: #e5e9ef;
                border-color: #414b5a;
            }

            #settingToggleButton:pressed {
                background: #1d232c;
            }

            #settingToggleButton[active="true"] {
                background: #1677ff;
                color: #ffffff;
                border: 1px solid #1677ff;
            }

            #settingToggleButton[active="true"]:hover {
                background: #2b86ff;
                border-color: #2b86ff;
            }

            #settingToggleButton[active="true"]:pressed {
                background: #0f64d8;
                border-color: #0f64d8;
            }

            #autoToggleButton {
                background: #242a33;
                color: #aeb6c2;
                border: 1px solid #343c48;
                border-radius: 12px;
                padding: 6px 12px;
                font-size: 11px;
                font-weight: 700;
                min-width: 72px;
            }

            #autoToggleButton:hover {
                background: #2d3541;
                border-color: #414b5a;
            }

            #autoToggleButton:pressed {
                background: #1d232c;
            }

            #autoToggleButton[active="true"] {
                background: #1677ff;
                color: #ffffff;
                border-color: #1677ff;
            }

            #autoToggleButton[active="true"]:hover {
                background: #2b86ff;
            }

            #autoToggleButton[active="true"]:pressed {
                background: #0f64d8;
            }
        )");
    }

    if (autoGamingModeButton != nullptr)
    {
        autoGamingModeButton->style()->unpolish(
            autoGamingModeButton
        );

        autoGamingModeButton->style()->polish(
            autoGamingModeButton
        );
    }

    if (cpuPriorityButton != nullptr)
    {
        cpuPriorityButton->style()->unpolish(
            cpuPriorityButton
        );

        cpuPriorityButton->style()->polish(
            cpuPriorityButton
        );
    }

    if (backgroundOptimizationButton != nullptr)
    {
        backgroundOptimizationButton->style()->unpolish(
            backgroundOptimizationButton
        );

        backgroundOptimizationButton->style()->polish(
            backgroundOptimizationButton
        );
    }

    if (modeToggleButton != nullptr)
    {
        modeToggleButton->style()->unpolish(
            modeToggleButton
        );

        modeToggleButton->style()->polish(
            modeToggleButton
        );
    }
}