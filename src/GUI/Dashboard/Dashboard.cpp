#include "Dashboard.h"

#include "../../GPU/GPU.h"
#include "LiveGraph.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QVBoxLayout>

#include <iomanip>
#include <sstream>


namespace
{
    QString formatNumber(
        double value,
        int decimals = 1
    )
    {
        std::ostringstream stream;

        stream
            << std::fixed
            << std::setprecision(decimals)
            << value;

        return QString::fromStdString(
            stream.str()
        );
    }


    // =========================================================
    // TEMPERATURE COLOR
    // =========================================================

    QString temperatureColor(
        double temperature
    )
    {
        if (temperature < 60.0)
        {
            return "#48c9a5";
        }

        if (temperature < 80.0)
        {
            return "#f0c75e";
        }

        if (temperature < 90.0)
        {
            return "#ff9f68";
        }

        return "#ff5f6d";
    }


    // =========================================================
    // METRIC CARD
    // =========================================================

    QFrame* createMetricCard(
        const QString& title,
        const QString& accent,
        QLabel*& valueLabel,
        QLabel*& secondaryLabel,
        QProgressBar*& progressBar,
        LiveGraph*& graph,
        LiveGraph** temperatureGraph
    )
    {
        QFrame* card =
            new QFrame();

        card->setObjectName(
            "metricCard"
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


        // =====================================================
        // HEADER
        // =====================================================

        QHBoxLayout* header =
            new QHBoxLayout();

        header->setContentsMargins(
            0,
            0,
            0,
            0
        );

        header->setSpacing(
            0
        );


        QLabel* accentLabel =
            new QLabel("●");

        accentLabel->setObjectName(
            "metricAccent"
        );

        accentLabel->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 9px;"
            ).arg(accent)
        );


        QLabel* titleLabel =
            new QLabel(title);

        titleLabel->setObjectName(
            "metricTitle"
        );


        header->addWidget(
            accentLabel
        );

        header->addSpacing(
            7
        );

        header->addWidget(
            titleLabel
        );

        header->addStretch();


        layout->addLayout(
            header
        );


        // =====================================================
        // MAIN VALUE
        // =====================================================

        valueLabel =
            new QLabel("--");

        valueLabel->setObjectName(
            "metricValue"
        );


        layout->addWidget(
            valueLabel
        );


        // =====================================================
        // SECONDARY VALUE
        // =====================================================

        secondaryLabel =
            new QLabel("--");

        secondaryLabel->setObjectName(
            "metricSecondary"
        );


        layout->addWidget(
            secondaryLabel
        );


        // =====================================================
        // PROGRESS BAR
        // =====================================================

        progressBar =
            new QProgressBar();

        progressBar->setObjectName(
            "metricProgress"
        );

        progressBar->setRange(
            0,
            100
        );

        progressBar->setValue(
            0
        );

        progressBar->setTextVisible(
            false
        );

        progressBar->setFixedHeight(
            5
        );


        progressBar->setStyleSheet(
            QString(
                "QProgressBar {"
                " background: #20252d;"
                " border: none;"
                " border-radius: 2px;"
                "}"
                "QProgressBar::chunk {"
                " background: %1;"
                " border-radius: 2px;"
                "}"
            ).arg(accent)
        );


        layout->addSpacing(
            4
        );

        layout->addWidget(
            progressBar
        );


        // =====================================================
        // UTILIZATION GRAPH
        // =====================================================

        layout->addSpacing(
            5
        );


        graph =
            new LiveGraph(
                accent,
                card
            );


        layout->addWidget(
            graph
        );


        // =====================================================
        // TEMPERATURE GRAPH
        // =====================================================

        if (temperatureGraph != nullptr)
        {
            layout->addSpacing(
                4
            );


            *temperatureGraph =
                new LiveGraph(
                    "#48c9a5",
                    card
                );


            (*temperatureGraph)->setRange(
                30.0,
                100.0
            );


            layout->addWidget(
                *temperatureGraph
            );
        }


        return card;
    }
}


Dashboard::Dashboard(QWidget* parent)
    : QWidget(parent)
{
    setObjectName(
        "dashboard"
    );


    // =========================================================
    // MAIN LAYOUT
    // =========================================================

    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    mainLayout->setSpacing(
        18
    );


    // =========================================================
    // OVERVIEW HEADER
    // =========================================================

    QHBoxLayout* overviewHeader =
        new QHBoxLayout();

    overviewHeader->setContentsMargins(
        2,
        0,
        2,
        0
    );


    QVBoxLayout* overviewText =
        new QVBoxLayout();

    overviewText->setSpacing(
        2
    );


    QLabel* overviewTitle =
        new QLabel(
            "Performance"
        );

    overviewTitle->setObjectName(
        "overviewTitle"
    );


    QLabel* overviewSubtitle =
        new QLabel(
            "Live hardware utilization"
        );

    overviewSubtitle->setObjectName(
        "overviewSubtitle"
    );


    overviewText->addWidget(
        overviewTitle
    );

    overviewText->addWidget(
        overviewSubtitle
    );


    overviewHeader->addLayout(
        overviewText
    );

    overviewHeader->addStretch();


    QLabel* updateLabel =
        new QLabel(
            "●  Live • 1s refresh"
        );

    updateLabel->setObjectName(
        "updateLabel"
    );


    overviewHeader->addWidget(
        updateLabel
    );


    mainLayout->addLayout(
        overviewHeader
    );


    // =========================================================
    // MAIN METRIC CARDS
    // =========================================================

    QGridLayout* metrics =
        new QGridLayout();

    metrics->setContentsMargins(
        0,
        0,
        0,
        0
    );

    metrics->setHorizontalSpacing(
        14
    );

    metrics->setVerticalSpacing(
        14
    );


    // =========================================================
    // CPU
    // =========================================================

    QFrame* cpuCard =
        createMetricCard(
            "CPU",
            "#6f8cff",
            cpuUsageLabel,
            cpuTemperatureLabel,
            cpuProgressBar,
            cpuGraph,
            &cpuTemperatureGraph
        );


    cpuCard->setStyleSheet(
        "QFrame {"
        " background: #131827;"
        " border: 1px solid #29344f;"
        " border-radius: 12px;"
        "}"
    );


    // =========================================================
    // GPU
    // =========================================================

    QFrame* gpuCard =
        createMetricCard(
            "GPU",
            "#a879ff",
            gpuUsageLabel,
            gpuTemperatureLabel,
            gpuProgressBar,
            gpuGraph,
            &gpuTemperatureGraph
        );


    gpuCard->setStyleSheet(
        "QFrame {"
        " background: #171427;"
        " border: 1px solid #3a2c54;"
        " border-radius: 12px;"
        "}"
    );


    // =========================================================
    // MEMORY
    // =========================================================

    QFrame* ramCard =
        createMetricCard(
            "MEMORY",
            "#48c9a5",
            ramUsageLabel,
            ramPercentageLabel,
            ramProgressBar,
            ramGraph,
            nullptr
        );


    ramCard->setStyleSheet(
        "QFrame {"
        " background: #10201d;"
        " border: 1px solid #25483f;"
        " border-radius: 12px;"
        "}"
    );


    // =========================================================
    // ADD CARDS
    // =========================================================

    metrics->addWidget(
        cpuCard,
        0,
        0
    );

    metrics->addWidget(
        gpuCard,
        0,
        1
    );

    metrics->addWidget(
        ramCard,
        0,
        2
    );


    metrics->setColumnStretch(
        0,
        1
    );

    metrics->setColumnStretch(
        1,
        1
    );

    metrics->setColumnStretch(
        2,
        1
    );


    mainLayout->addLayout(
        metrics
    );


    // =========================================================
    // GPU DETAILS
    // =========================================================

    QFrame* gpuInfo =
        new QFrame();

    gpuInfo->setObjectName(
        "infoCard"
    );


    QHBoxLayout* gpuInfoLayout =
        new QHBoxLayout(gpuInfo);

    gpuInfoLayout->setContentsMargins(
        18,
        12,
        18,
        12
    );


    QLabel* gpuInfoTitle =
        new QLabel(
            "GRAPHICS"
        );

    gpuInfoTitle->setObjectName(
        "infoTitle"
    );


    gpuNameLabel =
        new QLabel(
            "GPU: --"
        );

    gpuNameLabel->setObjectName(
        "infoText"
    );


    gpuVramLabel =
        new QLabel(
            "VRAM: --"
        );

    gpuVramLabel->setObjectName(
        "infoText"
    );


    gpuInfoLayout->addWidget(
        gpuInfoTitle
    );

    gpuInfoLayout->addSpacing(
        14
    );

    gpuInfoLayout->addWidget(
        gpuNameLabel
    );

    gpuInfoLayout->addStretch();

    gpuInfoLayout->addWidget(
        gpuVramLabel
    );


    mainLayout->addWidget(
        gpuInfo
    );


    // =========================================================
    // DISK + NETWORK
    // =========================================================

    QGridLayout* ioLayout =
        new QGridLayout();

    ioLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    ioLayout->setHorizontalSpacing(
        14
    );


    // =========================================================
    // STORAGE
    // =========================================================

    QFrame* diskCard =
        new QFrame();

    diskCard->setObjectName(
        "smallCard"
    );


    QVBoxLayout* diskLayout =
        new QVBoxLayout(diskCard);

    diskLayout->setContentsMargins(
        18,
        14,
        18,
        14
    );

    diskLayout->setSpacing(
        6
    );


    QLabel* diskTitle =
        new QLabel(
            "STORAGE"
        );

    diskTitle->setObjectName(
        "smallTitle"
    );


    diskReadLabel =
        new QLabel(
            "Read   -- MB/s"
        );

    diskReadLabel->setObjectName(
        "smallValue"
    );


    diskWriteLabel =
        new QLabel(
            "Write  -- MB/s"
        );

    diskWriteLabel->setObjectName(
        "smallValue"
    );


    diskLayout->addWidget(
        diskTitle
    );

    diskLayout->addWidget(
        diskReadLabel
    );

    diskLayout->addWidget(
        diskWriteLabel
    );


    // =========================================================
    // NETWORK
    // =========================================================

    QFrame* networkCard =
        new QFrame();

    networkCard->setObjectName(
        "smallCard"
    );


    QVBoxLayout* networkLayout =
        new QVBoxLayout(networkCard);

    networkLayout->setContentsMargins(
        18,
        14,
        18,
        14
    );

    networkLayout->setSpacing(
        6
    );


    QLabel* networkTitle =
        new QLabel(
            "NETWORK"
        );

    networkTitle->setObjectName(
        "smallTitle"
    );


    networkDownloadLabel =
        new QLabel(
            "↓   -- MB/s"
        );

    networkDownloadLabel->setObjectName(
        "smallValue"
    );


    networkUploadLabel =
        new QLabel(
            "↑   -- MB/s"
        );

    networkUploadLabel->setObjectName(
        "smallValue"
    );


    networkLayout->addWidget(
        networkTitle
    );

    networkLayout->addWidget(
        networkDownloadLabel
    );

    networkLayout->addWidget(
        networkUploadLabel
    );


    ioLayout->addWidget(
        diskCard,
        0,
        0
    );

    ioLayout->addWidget(
        networkCard,
        0,
        1
    );


    ioLayout->setColumnStretch(
        0,
        1
    );

    ioLayout->setColumnStretch(
        1,
        1
    );


    mainLayout->addLayout(
        ioLayout
    );


    // =========================================================
    // SYSTEM FOOTER
    // =========================================================

    QFrame* systemCard =
        new QFrame();

    systemCard->setObjectName(
        "systemCard"
    );


    QHBoxLayout* systemLayout =
        new QHBoxLayout(systemCard);

    systemLayout->setContentsMargins(
        18,
        10,
        18,
        10
    );


    QLabel* systemLabel =
        new QLabel(
            "SYSTEM"
        );

    systemLabel->setObjectName(
        "smallTitle"
    );


    uptimeLabel =
        new QLabel(
            "Uptime  --"
        );

    uptimeLabel->setObjectName(
        "systemValue"
    );


    systemLayout->addWidget(
        systemLabel
    );

    systemLayout->addStretch();

    systemLayout->addWidget(
        uptimeLabel
    );


    mainLayout->addWidget(
        systemCard
    );


    mainLayout->addStretch();


    // =========================================================
    // GLOBAL STYLE
    // =========================================================

    setStyleSheet(
        "QWidget#dashboard {"
        "background: transparent;"
        "}"

        "#overviewTitle {"
        "color: #eef1f6;"
        "font-size: 17px;"
        "font-weight: 750;"
        "}"

        "#overviewSubtitle {"
        "color: #687285;"
        "font-size: 11px;"
        "}"

        "#updateLabel {"
        "color: #56c98b;"
        "font-size: 10px;"
        "font-weight: 650;"
        "}"

        "#metricCard {"
        "border-radius: 12px;"
        "}"

        "#metricTitle {"
        "color: #7d8798;"
        "font-size: 10px;"
        "font-weight: 800;"
        "letter-spacing: 1.3px;"
        "}"

        "#metricValue {"
        "color: #f2f4f7;"
        "font-size: 30px;"
        "font-weight: 750;"
        "}"

        "#metricSecondary {"
        "color: #7a8495;"
        "font-size: 11px;"
        "}"

        "#infoCard {"
        "background: #12101b;"
        "border: 1px solid #30283f;"
        "border-radius: 9px;"
        "}"

        "#infoTitle {"
        "color: #8d73bd;"
        "font-size: 9px;"
        "font-weight: 800;"
        "letter-spacing: 1.3px;"
        "}"

        "#infoText {"
        "color: #818b9b;"
        "font-size: 10px;"
        "font-weight: 600;"
        "}"

        "#smallCard {"
        "background: #11151c;"
        "border: 1px solid #252c37;"
        "border-radius: 11px;"
        "}"

        "#smallCard:hover {"
        "background: #141922;"
        "border: 1px solid #303949;"
        "}"

        "#smallTitle {"
        "color: #626d7f;"
        "font-size: 9px;"
        "font-weight: 800;"
        "letter-spacing: 1.4px;"
        "}"

        "#smallValue {"
        "color: #d9dee6;"
        "font-size: 13px;"
        "font-weight: 600;"
        "}"

        "#systemCard {"
        "background: #0f1319;"
        "border: 1px solid #202732;"
        "border-radius: 9px;"
        "}"

        "#systemValue {"
        "color: #929baa;"
        "font-size: 10px;"
        "font-weight: 600;"
        "}"
    );


    // =========================================================
    // INITIAL UPDATE
    // =========================================================

    updateStats();


    // =========================================================
    // TIMER
    // =========================================================

    QTimer* timer =
        new QTimer(this);


    connect(
        timer,
        &QTimer::timeout,
        this,
        &Dashboard::updateStats
    );


    timer->start(
        1000
    );
}


void Dashboard::updateStats()
{
    Monitoring::SystemStats stats =
        Monitoring::Update();


    // =========================================================
    // CPU
    // =========================================================

    cpuUsageLabel->setText(
        formatNumber(
            stats.cpuUsage,
            0
        ) + " %"
    );


    cpuProgressBar->setValue(
        qBound(
            0,
            static_cast<int>(
                stats.cpuUsage
            ),
            100
        )
    );


    cpuGraph->addValue(
        stats.cpuUsage
    );


    // =========================================================
    // CPU TEMPERATURE
    // =========================================================

    if (stats.cpuTemperature >= 0.0)
    {
        const QString color =
            temperatureColor(
                stats.cpuTemperature
            );


        cpuTemperatureLabel->setText(
            "Temperature  " +
            formatNumber(
                stats.cpuTemperature,
                1
            ) +
            " °C"
        );


        cpuTemperatureLabel->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 11px;"
            ).arg(color)
        );


        cpuTemperatureGraph->setLineColor(
            color
        );


        cpuTemperatureGraph->addValue(
            stats.cpuTemperature
        );
    }
    else
    {
        cpuTemperatureLabel->setText(
            "Temperature  N/A"
        );


        cpuTemperatureLabel->setStyleSheet(
            "color: #7a8495;"
            "font-size: 11px;"
        );
    }


    // =========================================================
    // GPU
    // =========================================================

    if (stats.gpuUsage >= 0.0)
    {
        gpuUsageLabel->setText(
            formatNumber(
                stats.gpuUsage,
                0
            ) + " %"
        );


        gpuProgressBar->setValue(
            qBound(
                0,
                static_cast<int>(
                    stats.gpuUsage
                ),
                100
            )
        );


        gpuGraph->addValue(
            stats.gpuUsage
        );
    }
    else
    {
        gpuUsageLabel->setText(
            "N/A"
        );


        gpuProgressBar->setValue(
            0
        );
    }


    // =========================================================
    // GPU TEMPERATURE
    // =========================================================

    if (stats.gpuTemperature >= 0.0)
    {
        const QString color =
            temperatureColor(
                stats.gpuTemperature
            );


        gpuTemperatureLabel->setText(
            "Temperature  " +
            formatNumber(
                stats.gpuTemperature,
                1
            ) +
            " °C"
        );


        gpuTemperatureLabel->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 11px;"
            ).arg(color)
        );


        gpuTemperatureGraph->setLineColor(
            color
        );


        gpuTemperatureGraph->addValue(
            stats.gpuTemperature
        );
    }
    else
    {
        gpuTemperatureLabel->setText(
            "Temperature  N/A"
        );


        gpuTemperatureLabel->setStyleSheet(
            "color: #7a8495;"
            "font-size: 11px;"
        );
    }


    // =========================================================
    // GPU INFO
    // =========================================================

    gpuNameLabel->setText(
        QString::fromStdString(
            GPU::GetName()
        )
    );


    if (stats.gpuVramUsedGB >= 0.0)
    {
        gpuVramLabel->setText(
            "VRAM Used  " +
            formatNumber(
                stats.gpuVramUsedGB,
                2
            ) +
            " GB"
        );
    }
    else
    {
        gpuVramLabel->setText(
            "VRAM Used  N/A"
        );
    }


    // =========================================================
    // RAM
    // =========================================================

    ramUsageLabel->setText(
        formatNumber(
            stats.ramUsedGB,
            1
        ) +
        " / " +
        formatNumber(
            stats.ramTotalGB,
            1
        ) +
        " GB"
    );


    ramPercentageLabel->setText(
        formatNumber(
            stats.ramUsagePercent,
            0
        ) +
        " % used"
    );


    ramProgressBar->setValue(
        qBound(
            0,
            static_cast<int>(
                stats.ramUsagePercent
            ),
            100
        )
    );


    ramGraph->addValue(
        stats.ramUsagePercent
    );


    // =========================================================
    // DISK
    // =========================================================

    diskReadLabel->setText(
        "Read   " +
        formatNumber(
            stats.diskReadMBps,
            1
        ) +
        " MB/s"
    );


    diskWriteLabel->setText(
        "Write  " +
        formatNumber(
            stats.diskWriteMBps,
            1
        ) +
        " MB/s"
    );


    // =========================================================
    // NETWORK
    // =========================================================

    networkDownloadLabel->setText(
        "↓   " +
        formatNumber(
            stats.networkDownloadMBps,
            2
        ) +
        " MB/s"
    );


    networkUploadLabel->setText(
        "↑   " +
        formatNumber(
            stats.networkUploadMBps,
            2
        ) +
        " MB/s"
    );


    // =========================================================
    // UPTIME
    // =========================================================

    unsigned long long hours =
        stats.uptimeSeconds / 3600;


    unsigned long long minutes =
        (stats.uptimeSeconds % 3600) / 60;


    uptimeLabel->setText(
        "Uptime  " +
        QString::number(hours) +
        "h " +
        QString::number(minutes) +
        "m"
    );
}