#include "Dashboard.h"

#include "../../GPU/GPU.h"
#include "../../System/System.h"
#include "LiveGraph.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QStyle>
#include <QVBoxLayout>

#include <iomanip>
#include <sstream>


namespace
{
    constexpr int CardHeight = 400;

    constexpr int HeaderHeight = 18;
    constexpr int MainValueHeight = 42;
    constexpr int DescriptionHeight = 16;

    constexpr int MainGraphHeight = 60;
    constexpr int SecondaryRowHeight = 29;
    constexpr int SecondaryGraphHeight = 60;

    constexpr int ProgressHeight = 5;


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


    QString temperatureColor(
        double temperature
    )
    {
        if (temperature < 60.0)
        {
            return "#4fd1a5";
        }

        if (temperature < 80.0)
        {
            return "#e8c35c";
        }

        if (temperature < 90.0)
        {
            return "#ee9564";
        }

        return "#ef6675";
    }


    QFrame* createTemperatureBadge(
        QLabel*& valueLabel,
        const QString& title,
        QWidget* parent
    )
    {
        QFrame* badge =
            new QFrame(parent);

        badge->setObjectName(
            "temperatureBadge"
        );

        badge->setFixedHeight(
            SecondaryRowHeight
        );

        QHBoxLayout* layout =
            new QHBoxLayout(badge);

        layout->setContentsMargins(
            10,
            4,
            10,
            4
        );

        layout->setSpacing(
            7
        );

        QLabel* titleLabel =
            new QLabel(
                title,
                badge
            );

        titleLabel->setObjectName(
            "temperatureTitle"
        );

        valueLabel =
            new QLabel(
                "-- °C",
                badge
            );

        valueLabel->setObjectName(
            "temperatureValue"
        );

        layout->addWidget(
            titleLabel
        );

        layout->addStretch();

        layout->addWidget(
            valueLabel
        );

        return badge;
    }


    QFrame* createEmptyAlignmentRow(
        QWidget* parent
    )
    {
        QFrame* row =
            new QFrame(parent);

        row->setFixedHeight(
            SecondaryRowHeight
        );

        row->setAttribute(
            Qt::WA_TransparentForMouseEvents
        );

        return row;
    }


    QFrame* createEmptyAlignmentGraph(
        QWidget* parent
    )
    {
        QFrame* graph =
            new QFrame(parent);

        graph->setFixedHeight(
            SecondaryGraphHeight
        );

        graph->setAttribute(
            Qt::WA_TransparentForMouseEvents
        );

        return graph;
    }


    QFrame* createMetricCard(
        const QString& title,
        const QString& accent,
        QLabel*& valueLabel,
        QLabel*& secondaryLabel,
        QProgressBar*& progressBar,
        LiveGraph*& graph
    )
    {
        QFrame* card =
            new QFrame();

        card->setObjectName(
            "mainMetricCard"
        );

        card->setFixedHeight(
            CardHeight
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
            0
        );


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

        header->setAlignment(
            Qt::AlignVCenter
        );


        QLabel* accentDot =
            new QLabel(
                "●",
                card
            );

        accentDot->setFixedHeight(
            HeaderHeight
        );

        accentDot->setAlignment(
            Qt::AlignVCenter
        );

        accentDot->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 8px;"
            ).arg(accent)
        );


        QLabel* titleLabel =
            new QLabel(
                title,
                card
            );

        titleLabel->setObjectName(
            "cardTitle"
        );

        titleLabel->setFixedHeight(
            HeaderHeight
        );

        titleLabel->setAlignment(
            Qt::AlignVCenter
        );


        QLabel* liveLabel =
            new QLabel(
                "LIVE",
                card
            );

        liveLabel->setObjectName(
            "cardLive"
        );

        liveLabel->setFixedHeight(
            HeaderHeight
        );

        liveLabel->setAlignment(
            Qt::AlignVCenter
        );


        header->addWidget(
            accentDot
        );

        header->addSpacing(
            6
        );

        header->addWidget(
            titleLabel
        );

        header->addStretch();

        header->addWidget(
            liveLabel
        );


        layout->addLayout(
            header
        );

        layout->addSpacing(
            5
        );


        valueLabel =
            new QLabel(
                "-- %",
                card
            );

        valueLabel->setObjectName(
            "bigMetricValue"
        );

        valueLabel->setFixedHeight(
            MainValueHeight
        );

        valueLabel->setAlignment(
            Qt::AlignLeft |
            Qt::AlignVCenter
        );

        layout->addWidget(
            valueLabel
        );


        secondaryLabel =
            new QLabel(
                title == "MEMORY"
                    ? "Memory usage"
                    : "Utilization",
                card
            );

        secondaryLabel->setObjectName(
            "metricDescription"
        );

        secondaryLabel->setFixedHeight(
            DescriptionHeight
        );

        secondaryLabel->setAlignment(
            Qt::AlignLeft |
            Qt::AlignVCenter
        );

        layout->addWidget(
            secondaryLabel
        );

        layout->addSpacing(
            4
        );


        progressBar =
            new QProgressBar(
                card
            );

        progressBar->setObjectName(
            "metricProgressBar"
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
            ProgressHeight
        );

        progressBar->setProperty(
            "accentColor",
            accent
        );

        layout->addWidget(
            progressBar
        );

        layout->addSpacing(
            7
        );


        graph =
            new LiveGraph(
                accent,
                card
            );

        graph->setRange(
            0.0,
            100.0
        );

        graph->setFixedHeight(
            MainGraphHeight
        );

        layout->addWidget(
            graph
        );

        layout->addSpacing(
            7
        );

        return card;
    }
}


Dashboard::Dashboard(
    QWidget* parent
)
    : QWidget(parent)
{
    setObjectName(
        "dashboard"
    );


    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    mainLayout->setSpacing(
        16
    );


    QHBoxLayout* header =
        new QHBoxLayout();

    header->setContentsMargins(
        2,
        0,
        2,
        0
    );


    QVBoxLayout* headerText =
        new QVBoxLayout();

    headerText->setSpacing(
        2
    );


    QLabel* title =
        new QLabel(
            "Performance",
            this
        );

    title->setObjectName(
        "pageTitle"
    );


    QLabel* subtitle =
        new QLabel(
            "Real-time system overview",
            this
        );

    subtitle->setObjectName(
        "pageSubtitle"
    );


    headerText->addWidget(
        title
    );

    headerText->addWidget(
        subtitle
    );


    header->addLayout(
        headerText
    );

    header->addStretch();


    QLabel* status =
        new QLabel(
            "●  System monitoring active",
            this
        );

    status->setObjectName(
        "systemStatus"
    );


    header->addWidget(
        status
    );

    mainLayout->addLayout(
        header
    );


    QGridLayout* cards =
        new QGridLayout();

    cards->setContentsMargins(
        0,
        0,
        0,
        0
    );

    cards->setHorizontalSpacing(
        12
    );

    cards->setVerticalSpacing(
        12
    );


    QLabel* cpuDescriptionLabel =
        nullptr;


    QFrame* cpuCard =
        createMetricCard(
            "CPU",
            "#6f8cff",
            cpuUsageLabel,
            cpuDescriptionLabel,
            cpuProgressBar,
            cpuGraph
        );

    cpuCard->setProperty(
        "cardType",
        "cpu"
    );


    QVBoxLayout* cpuLayout =
        qobject_cast<QVBoxLayout*>(
            cpuCard->layout()
        );


    cpuTemperatureLabel =
        nullptr;


    QFrame* cpuTemperatureBadge =
        createTemperatureBadge(
            cpuTemperatureLabel,
            "Temperature",
            cpuCard
        );


    if (cpuLayout != nullptr)
    {
        cpuLayout->addWidget(
            cpuTemperatureBadge
        );
    }


    cpuTemperatureGraph =
        new LiveGraph(
            "#6f8cff",
            cpuCard
        );

    cpuTemperatureGraph->setRange(
        20.0,
        110.0
    );

    cpuTemperatureGraph->setFixedHeight(
        SecondaryGraphHeight
    );


    if (cpuLayout != nullptr)
    {
        cpuLayout->addSpacing(
            5
        );

        cpuLayout->addWidget(
            cpuTemperatureGraph
        );
    }


    if (cpuLayout != nullptr)
    {
        cpuLayout->addSpacing(
            5
        );

        cpuLayout->addWidget(
            createEmptyAlignmentRow(cpuCard)
        );

        cpuLayout->addSpacing(
            5
        );

        cpuLayout->addWidget(
            createEmptyAlignmentGraph(cpuCard)
        );
    }


    QLabel* gpuDescriptionLabel =
        nullptr;


    QFrame* gpuCard =
        createMetricCard(
            "GPU",
            "#a879ff",
            gpuUsageLabel,
            gpuDescriptionLabel,
            gpuProgressBar,
            gpuGraph
        );

    gpuCard->setProperty(
        "cardType",
        "gpu"
    );


    QVBoxLayout* gpuLayout =
        qobject_cast<QVBoxLayout*>(
            gpuCard->layout()
        );


    gpuTemperatureLabel =
        nullptr;


    QFrame* gpuTemperatureBadge =
        createTemperatureBadge(
            gpuTemperatureLabel,
            "Temperature",
            gpuCard
        );


    if (gpuLayout != nullptr)
    {
        gpuLayout->addWidget(
            gpuTemperatureBadge
        );
    }


    gpuTemperatureGraph =
        new LiveGraph(
            "#a879ff",
            gpuCard
        );

    gpuTemperatureGraph->setRange(
        20.0,
        110.0
    );

    gpuTemperatureGraph->setFixedHeight(
        SecondaryGraphHeight
    );


    if (gpuLayout != nullptr)
    {
        gpuLayout->addSpacing(
            5
        );

        gpuLayout->addWidget(
            gpuTemperatureGraph
        );
    }


    QFrame* hotspotRow =
        new QFrame(
            gpuCard
        );

    hotspotRow->setObjectName(
        "hotspotRow"
    );

    hotspotRow->setFixedHeight(
        SecondaryRowHeight
    );


    QHBoxLayout* hotspotLayout =
        new QHBoxLayout(
            hotspotRow
        );

    hotspotLayout->setContentsMargins(
        10,
        4,
        10,
        4
    );

    hotspotLayout->setSpacing(
        6
    );


    QLabel* hotspotTitle =
        new QLabel(
            "GPU Hotspot",
            hotspotRow
        );

    hotspotTitle->setObjectName(
        "hotspotTitle"
    );


    gpuHotspotLabel =
        new QLabel(
            "-- °C",
            hotspotRow
        );

    gpuHotspotLabel->setObjectName(
        "hotspotValue"
    );


    hotspotLayout->addWidget(
        hotspotTitle
    );

    hotspotLayout->addStretch();

    hotspotLayout->addWidget(
        gpuHotspotLabel
    );


    if (gpuLayout != nullptr)
    {
        gpuLayout->addSpacing(
            5
        );

        gpuLayout->addWidget(
            hotspotRow
        );
    }


    gpuHotspotGraph =
        new LiveGraph(
            "#9b82d0",
            gpuCard
        );

    gpuHotspotGraph->setRange(
        30.0,
        120.0
    );

    gpuHotspotGraph->setFixedHeight(
        SecondaryGraphHeight
    );


    if (gpuLayout != nullptr)
    {
        gpuLayout->addSpacing(
            5
        );

        gpuLayout->addWidget(
            gpuHotspotGraph
        );
    }


    QFrame* ramCard =
        createMetricCard(
            "MEMORY",
            "#48c9a5",
            ramUsageLabel,
            ramPercentageLabel,
            ramProgressBar,
            ramGraph
        );

    ramCard->setProperty(
        "cardType",
        "ram"
    );


    ramPercentageLabel->setObjectName(
        "memoryPercentage"
    );


    QVBoxLayout* ramLayout =
        qobject_cast<QVBoxLayout*>(
            ramCard->layout()
        );


    QFrame* memoryInfoRow =
        new QFrame(
            ramCard
        );

    memoryInfoRow->setObjectName(
        "memoryInfoRow"
    );

    memoryInfoRow->setFixedHeight(
        SecondaryRowHeight
    );


    QHBoxLayout* memoryInfoLayout =
        new QHBoxLayout(
            memoryInfoRow
        );

    memoryInfoLayout->setContentsMargins(
        10,
        4,
        10,
        4
    );


    QLabel* memoryInfoTitle =
        new QLabel(
            "Memory",
            memoryInfoRow
        );

    memoryInfoTitle->setObjectName(
        "memoryInfoTitle"
    );


    QLabel* memoryInfoValue =
        new QLabel(
            "Physical memory",
            memoryInfoRow
        );

    memoryInfoValue->setObjectName(
        "memoryInfoValue"
    );


    memoryInfoLayout->addWidget(
        memoryInfoTitle
    );

    memoryInfoLayout->addStretch();

    memoryInfoLayout->addWidget(
        memoryInfoValue
    );


    if (ramLayout != nullptr)
    {
        ramLayout->addWidget(
            memoryInfoRow
        );

        ramLayout->addSpacing(
            5
        );

        ramLayout->addWidget(
            createEmptyAlignmentGraph(ramCard)
        );

        ramLayout->addSpacing(
            5
        );

        ramLayout->addWidget(
            createEmptyAlignmentRow(ramCard)
        );

        ramLayout->addSpacing(
            5
        );

        ramLayout->addWidget(
            createEmptyAlignmentGraph(ramCard)
        );
    }


    cards->addWidget(
        cpuCard,
        0,
        0
    );

    cards->addWidget(
        gpuCard,
        0,
        1
    );

    cards->addWidget(
        ramCard,
        0,
        2
    );


    cards->setColumnStretch(
        0,
        1
    );

    cards->setColumnStretch(
        1,
        1
    );

    cards->setColumnStretch(
        2,
        1
    );


    mainLayout->addLayout(
        cards
    );


    QFrame* infoArea =
        new QFrame(
            this
        );

    infoArea->setObjectName(
        "infoArea"
    );


    QVBoxLayout* infoLayout =
        new QVBoxLayout(infoArea);

    infoLayout->setContentsMargins(
        18,
        14,
        18,
        14
    );

    infoLayout->setSpacing(
        12
    );


    QLabel* infoTitle =
        new QLabel(
            "SYSTEM INFORMATION",
            infoArea
        );

    infoTitle->setObjectName(
        "infoSectionTitle"
    );


    infoLayout->addWidget(
        infoTitle
    );


    QHBoxLayout* cpuInfoRow =
        new QHBoxLayout();

    cpuInfoRow->setContentsMargins(
        0,
        0,
        0,
        0
    );


    QLabel* processorLabel =
        new QLabel(
            "Processor",
            infoArea
        );

    processorLabel->setObjectName(
        "infoLabel"
    );


    cpuNameLabel =
        new QLabel(
            "--",
            infoArea
        );

    cpuNameLabel->setObjectName(
        "infoPrimary"
    );


    cpuInfoRow->addWidget(
        processorLabel
    );

    cpuInfoRow->addSpacing(
        20
    );

    cpuInfoRow->addWidget(
        cpuNameLabel
    );

    cpuInfoRow->addStretch();

    infoLayout->addLayout(
        cpuInfoRow
    );


    QHBoxLayout* gpuRow =
        new QHBoxLayout();

    gpuRow->setContentsMargins(
        0,
        0,
        0,
        0
    );


    QLabel* graphicsLabel =
        new QLabel(
            "Graphics",
            infoArea
        );

    graphicsLabel->setObjectName(
        "infoLabel"
    );


    gpuNameLabel =
        new QLabel(
            "--",
            infoArea
        );

    gpuNameLabel->setObjectName(
        "infoPrimary"
    );


    gpuVramLabel =
        new QLabel(
            "VRAM  --",
            infoArea
        );

    gpuVramLabel->setObjectName(
        "infoSecondary"
    );


    gpuRow->addWidget(
        graphicsLabel
    );

    gpuRow->addSpacing(
        20
    );

    gpuRow->addWidget(
        gpuNameLabel
    );

    gpuRow->addStretch();

    gpuRow->addWidget(
        gpuVramLabel
    );

    infoLayout->addLayout(
        gpuRow
    );


    QFrame* divider =
        new QFrame(
            infoArea
        );

    divider->setFrameShape(
        QFrame::HLine
    );

    divider->setObjectName(
        "infoDivider"
    );

    infoLayout->addWidget(
        divider
    );


    QHBoxLayout* ioRow =
        new QHBoxLayout();

    ioRow->setContentsMargins(
        0,
        0,
        0,
        0
    );


    QLabel* storageLabel =
        new QLabel(
            "Storage",
            infoArea
        );

    storageLabel->setObjectName(
        "infoLabel"
    );


    diskReadLabel =
        new QLabel(
            "Read  -- MB/s",
            infoArea
        );

    diskReadLabel->setObjectName(
        "infoPrimary"
    );


    diskWriteLabel =
        new QLabel(
            "Write  -- MB/s",
            infoArea
        );

    diskWriteLabel->setObjectName(
        "infoSecondary"
    );


    ioRow->addWidget(
        storageLabel
    );

    ioRow->addSpacing(
        20
    );

    ioRow->addWidget(
        diskReadLabel
    );

    ioRow->addSpacing(
        12
    );

    ioRow->addWidget(
        diskWriteLabel
    );


    ioRow->addSpacing(
        35
    );


    QLabel* networkLabel =
        new QLabel(
            "Network",
            infoArea
        );

    networkLabel->setObjectName(
        "infoLabel"
    );


    networkDownloadLabel =
        new QLabel(
            "↓  -- MB/s",
            infoArea
        );

    networkDownloadLabel->setObjectName(
        "infoPrimary"
    );


    networkUploadLabel =
        new QLabel(
            "↑  -- MB/s",
            infoArea
        );

    networkUploadLabel->setObjectName(
        "infoSecondary"
    );


    ioRow->addWidget(
        networkLabel
    );

    ioRow->addSpacing(
        20
    );

    ioRow->addWidget(
        networkDownloadLabel
    );

    ioRow->addSpacing(
        12
    );

    ioRow->addWidget(
        networkUploadLabel
    );


    ioRow->addStretch();


    uptimeLabel =
        new QLabel(
            "Uptime  --",
            infoArea
        );

    uptimeLabel->setObjectName(
        "infoPrimary"
    );


    ioRow->addWidget(
        uptimeLabel
    );

    infoLayout->addLayout(
        ioRow
    );


    mainLayout->addWidget(
        infoArea
    );

    mainLayout->addStretch();


    // =========================================================
    // INITIAL STYLE
    // =========================================================

    setLightMode(false);


    // =========================================================
    // UPDATE TIMER
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


void Dashboard::setLightMode(
    bool lightMode
)
{
    m_lightMode = lightMode;


    if (cpuGraph != nullptr)
    {
        cpuGraph->setDarkMode(!lightMode);
    }

    if (cpuTemperatureGraph != nullptr)
    {
        cpuTemperatureGraph->setDarkMode(!lightMode);
    }

    if (gpuGraph != nullptr)
    {
        gpuGraph->setDarkMode(!lightMode);
    }

    if (gpuTemperatureGraph != nullptr)
    {
        gpuTemperatureGraph->setDarkMode(!lightMode);
    }

    if (gpuHotspotGraph != nullptr)
    {
        gpuHotspotGraph->setDarkMode(!lightMode);
    }

    if (ramGraph != nullptr)
    {
        ramGraph->setDarkMode(!lightMode);
    }


    if (lightMode)
    {
        setStyleSheet(
            R"(

                QWidget#dashboard {
                    background: transparent;
                }

                #pageTitle {
                    color: #171a20;
                    font-size: 19px;
                    font-weight: 750;
                }

                #pageSubtitle {
                    color: #858d99;
                    font-size: 11px;
                }

                #systemStatus {
                    color: #35ad68;
                    font-size: 10px;
                    font-weight: 650;
                }

                QFrame#mainMetricCard[cardType="cpu"] {
                    background: #ffffff;
                    border: 1px solid #dfe3e9;
                    border-radius: 13px;
                }

                QFrame#mainMetricCard[cardType="gpu"] {
                    background: #ffffff;
                    border: 1px solid #e2ddec;
                    border-radius: 13px;
                }

                QFrame#mainMetricCard[cardType="ram"] {
                    background: #ffffff;
                    border: 1px solid #d8e7e1;
                    border-radius: 13px;
                }

                #cardTitle {
                    color: #626b78;
                    font-size: 10px;
                    font-weight: 800;
                }

                #cardLive {
                    color: #a0a7b1;
                    font-size: 8px;
                    font-weight: 800;
                }

                #bigMetricValue {
                    color: #171a20;
                    font-size: 32px;
                    font-weight: 750;
                }

                #metricDescription {
                    color: #7b8490;
                    font-size: 10px;
                }

                #memoryPercentage {
                    color: #718079;
                    font-size: 10px;
                }

                QProgressBar#metricProgressBar {
                    background: #e7eaee;
                    border: none;
                    border-radius: 2px;
                }

                QProgressBar#metricProgressBar::chunk {
                    background: #5273e8;
                    border-radius: 2px;
                }

                #temperatureBadge {
                    background: #f5f7f9;
                    border: 1px solid #e1e5ea;
                    border-radius: 7px;
                }

                #temperatureTitle {
                    color: #7b8490;
                    font-size: 9px;
                    font-weight: 600;
                }

                #temperatureValue {
                    color: #39414c;
                    font-size: 10px;
                    font-weight: 700;
                }

                #memoryInfoRow {
                    background: #f0f8f5;
                    border: 1px solid #d6e9e1;
                    border-radius: 7px;
                }

                #memoryInfoTitle {
                    color: #71857c;
                    font-size: 9px;
                    font-weight: 600;
                }

                #memoryInfoValue {
                    color: #299f78;
                    font-size: 10px;
                    font-weight: 700;
                }

                #hotspotRow {
                    background: #f6f3fa;
                    border: 1px solid #e3ddef;
                    border-radius: 7px;
                }

                #hotspotTitle {
                    color: #747b87;
                    font-size: 9px;
                }

                #hotspotValue {
                    color: #8065b9;
                    font-size: 10px;
                    font-weight: 700;
                }

                #infoArea {
                    background: #ffffff;
                    border: 1px solid #dfe3e9;
                    border-radius: 11px;
                }

                #infoSectionTitle {
                    color: #858d99;
                    font-size: 9px;
                    font-weight: 800;
                }

                #infoLabel {
                    color: #707985;
                    font-size: 10px;
                    font-weight: 700;
                }

                #infoPrimary {
                    color: #343a43;
                    font-size: 11px;
                    font-weight: 600;
                }

                #infoSecondary {
                    color: #7c8590;
                    font-size: 11px;
                    font-weight: 500;
                }

                #infoDivider {
                    color: #e1e5e9;
                    background: #e1e5e9;
                    max-height: 1px;
                }

            )"
        );
    }
    else
    {
        setStyleSheet(
            R"(

                QWidget#dashboard {
                    background: transparent;
                }

                #pageTitle {
                    color: #f0f2f6;
                    font-size: 19px;
                    font-weight: 750;
                }

                #pageSubtitle {
                    color: #687285;
                    font-size: 11px;
                }

                #systemStatus {
                    color: #54c98b;
                    font-size: 10px;
                    font-weight: 650;
                }

                QFrame#mainMetricCard[cardType="cpu"] {
                    background: #151a25;
                    border: 1px solid #29344b;
                    border-radius: 13px;
                }

                QFrame#mainMetricCard[cardType="gpu"] {
                    background: #181621;
                    border: 1px solid #352d4a;
                    border-radius: 13px;
                }

                QFrame#mainMetricCard[cardType="ram"] {
                    background: #141c1a;
                    border: 1px solid #29433c;
                    border-radius: 13px;
                }

                #cardTitle {
                    color: #8993a3;
                    font-size: 10px;
                    font-weight: 800;
                }

                #cardLive {
                    color: #505a69;
                    font-size: 8px;
                    font-weight: 800;
                }

                #bigMetricValue {
                    color: #f1f3f6;
                    font-size: 32px;
                    font-weight: 750;
                }

                #metricDescription {
                    color: #626c7b;
                    font-size: 10px;
                }

                #memoryPercentage {
                    color: #626c7b;
                    font-size: 10px;
                }

                QProgressBar#metricProgressBar {
                    background: #202630;
                    border: none;
                    border-radius: 2px;
                }

                QProgressBar#metricProgressBar::chunk {
                    background: #6f8cff;
                    border-radius: 2px;
                }

                #temperatureBadge {
                    background: #10141b;
                    border: 1px solid #252c37;
                    border-radius: 7px;
                }

                #temperatureTitle {
                    color: #687282;
                    font-size: 9px;
                    font-weight: 600;
                }

                #temperatureValue {
                    color: #dce1e8;
                    font-size: 10px;
                    font-weight: 700;
                }

                #memoryInfoRow {
                    background: #101714;
                    border: 1px solid #25352f;
                    border-radius: 7px;
                }

                #memoryInfoTitle {
                    color: #687a73;
                    font-size: 9px;
                    font-weight: 600;
                }

                #memoryInfoValue {
                    color: #4fd1a5;
                    font-size: 10px;
                    font-weight: 700;
                }

                #hotspotRow {
                    background: #11101a;
                    border: 1px solid #29243a;
                    border-radius: 7px;
                }

                #hotspotTitle {
                    color: #646e7e;
                    font-size: 9px;
                }

                #hotspotValue {
                    color: #9b82d0;
                    font-size: 10px;
                    font-weight: 700;
                }

                #infoArea {
                    background: #11151c;
                    border: 1px solid #252c36;
                    border-radius: 11px;
                }

                #infoSectionTitle {
                    color: #586273;
                    font-size: 9px;
                    font-weight: 800;
                }

                #infoLabel {
                    color: #697485;
                    font-size: 10px;
                    font-weight: 700;
                }

                #infoPrimary {
                    color: #d6dbe3;
                    font-size: 11px;
                    font-weight: 600;
                }

                #infoSecondary {
                    color: #737e8e;
                    font-size: 11px;
                    font-weight: 500;
                }

                #infoDivider {
                    color: #222832;
                    background: #222832;
                    max-height: 1px;
                }

            )"
        );
    }


    style()->unpolish(this);
    style()->polish(this);
    update();
}


void Dashboard::updateStats()
{
    Monitoring::SystemStats stats =
        Monitoring::Update();


    cpuUsageLabel->setText(
        formatNumber(
            stats.cpuUsage,
            0
        ) +
        " %"
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


    if (stats.cpuTemperature >= 0.0)
    {
        const QString color =
            temperatureColor(
                stats.cpuTemperature
            );


        cpuTemperatureLabel->setText(
            formatNumber(
                stats.cpuTemperature,
                1
            ) +
            " °C"
        );


        cpuTemperatureLabel->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 10px;"
                "font-weight: 700;"
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
            "N/A"
        );
    }


    if (stats.gpuUsage >= 0.0)
    {
        gpuUsageLabel->setText(
            formatNumber(
                stats.gpuUsage,
                0
            ) +
            " %"
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


    if (stats.gpuTemperature >= 0.0)
    {
        const QString color =
            temperatureColor(
                stats.gpuTemperature
            );


        gpuTemperatureLabel->setText(
            formatNumber(
                stats.gpuTemperature,
                1
            ) +
            " °C"
        );


        gpuTemperatureLabel->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 10px;"
                "font-weight: 700;"
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
            "N/A"
        );
    }


    if (stats.gpuHotspot >= 0.0)
    {
        const QString color =
            temperatureColor(
                stats.gpuHotspot
            );


        gpuHotspotLabel->setText(
            formatNumber(
                stats.gpuHotspot,
                1
            ) +
            " °C"
        );


        gpuHotspotLabel->setStyleSheet(
            QString(
                "color: %1;"
                "font-size: 10px;"
                "font-weight: 700;"
            ).arg(color)
        );


        gpuHotspotGraph->setLineColor(
            color
        );


        gpuHotspotGraph->addValue(
            stats.gpuHotspot
        );
    }
    else
    {
        gpuHotspotLabel->setText(
            "N/A"
        );
    }


    gpuNameLabel->setText(
        QString::fromStdString(
            GPU::GetName()
        )
    );


    if (
        stats.gpuVramUsedGB >= 0.0 &&
        stats.gpuVramTotalGB >= 0.0
    )
    {
        gpuVramLabel->setText(
            "VRAM  " +
            formatNumber(
                stats.gpuVramUsedGB,
                2
            ) +
            " / " +
            formatNumber(
                stats.gpuVramTotalGB,
                2
            ) +
            " GB"
        );
    }
    else if (
        stats.gpuVramUsedGB >= 0.0
    )
    {
        gpuVramLabel->setText(
            "VRAM  " +
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
            "VRAM  N/A"
        );
    }


    cpuNameLabel->setText(
        QString::fromLocal8Bit(
            System::GetCPUName()
        )
    );


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


    diskReadLabel->setText(
        "Read  " +
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


    networkDownloadLabel->setText(
        "↓  " +
        formatNumber(
            stats.networkDownloadMBps,
            2
        ) +
        " MB/s"
    );


    networkUploadLabel->setText(
        "↑  " +
        formatNumber(
            stats.networkUploadMBps,
            2
        ) +
        " MB/s"
    );


    const unsigned long long hours =
        stats.uptimeSeconds / 3600;


    const unsigned long long minutes =
        (stats.uptimeSeconds % 3600) / 60;


    uptimeLabel->setText(
        "Uptime  " +
        QString::number(hours) +
        "h " +
        QString::number(minutes) +
        "m"
    );
}