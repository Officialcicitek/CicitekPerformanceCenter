#include "MainWindow.h"

#include "Dashboard/Dashboard.h"
#include "GamingMode/GamingMode.h"
#include "Processes/Processes.h"

#include <QFrame>
#include <QStyle>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Cicitek Performance Center");

    resize(
        1360,
        820
    );

    setMinimumSize(
        1100,
        700
    );

    // =========================================================
    // CENTRAL WIDGET
    // =========================================================

    QWidget* central =
        new QWidget(this);

    central->setObjectName(
        "central"
    );

    setCentralWidget(
        central
    );

    QHBoxLayout* mainLayout =
        new QHBoxLayout(central);

    mainLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    mainLayout->setSpacing(
        0
    );

    // =========================================================
    // SIDEBAR
    // =========================================================

    QFrame* sidebar =
        new QFrame();

    sidebar->setObjectName(
        "sidebar"
    );

    sidebar->setFixedWidth(
        250
    );

    QVBoxLayout* sidebarLayout =
        new QVBoxLayout(sidebar);

    sidebarLayout->setContentsMargins(
        18,
        20,
        18,
        18
    );

    sidebarLayout->setSpacing(
        6
    );

    // =========================================================
    // BRAND
    // =========================================================

    QFrame* brandContainer =
        new QFrame();

    brandContainer->setObjectName(
        "brandContainer"
    );

    brandContainer->setFixedHeight(
        62
    );

    QHBoxLayout* brandLayout =
        new QHBoxLayout(
            brandContainer
        );

    brandLayout->setContentsMargins(
        8,
        0,
        8,
        0
    );

    brandLayout->setSpacing(
        11
    );

    QFrame* brandMark =
        new QFrame();

    brandMark->setObjectName(
        "brandMark"
    );

    brandMark->setFixedSize(
        34,
        34
    );

    QLabel* brandMarkText =
        new QLabel("C");

    brandMarkText->setObjectName(
        "brandMarkText"
    );

    QVBoxLayout* markLayout =
        new QVBoxLayout(
            brandMark
        );

    markLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    markLayout->setAlignment(
        Qt::AlignCenter
    );

    markLayout->addWidget(
        brandMarkText
    );

    QVBoxLayout* brandTextLayout =
        new QVBoxLayout();

    brandTextLayout->setSpacing(
        0
    );

    QLabel* brand =
        new QLabel(
            "CICITEK"
        );

    brand->setObjectName(
        "brand"
    );

    QLabel* brandSub =
        new QLabel(
            "PERFORMANCE CENTER"
        );

    brandSub->setObjectName(
        "brandSub"
    );

    brandTextLayout->addWidget(
        brand
    );

    brandTextLayout->addWidget(
        brandSub
    );

    brandLayout->addWidget(
        brandMark
    );

    brandLayout->addLayout(
        brandTextLayout
    );

    brandLayout->addStretch();

    sidebarLayout->addWidget(
        brandContainer
    );

    // =========================================================
    // NAVIGATION LABEL
    // =========================================================

    QLabel* navigation =
        new QLabel(
            "WORKSPACE"
        );

    navigation->setObjectName(
        "navigationLabel"
    );

    sidebarLayout->addSpacing(
        17
    );

    sidebarLayout->addWidget(
        navigation
    );

    sidebarLayout->addSpacing(
        7
    );

    // =========================================================
    // NAVIGATION BUTTONS
    // =========================================================

    QPushButton* dashboardButton =
        new QPushButton(
            "Dashboard"
        );

    QPushButton* gamingButton =
        new QPushButton(
            "Gaming Mode"
        );

    QPushButton* processesButton =
        new QPushButton(
            "Processes"
        );

    QPushButton* tweaksButton =
        new QPushButton(
            "Tweaks"
        );

    QPushButton* logsButton =
        new QPushButton(
            "Logs"
        );

    dashboardButton->setObjectName(
        "navActive"
    );

    gamingButton->setObjectName(
        "navButton"
    );

    processesButton->setObjectName(
        "navButton"
    );

    tweaksButton->setObjectName(
        "navButton"
    );

    logsButton->setObjectName(
        "navButton"
    );

    QList<QPushButton*> navButtons =
    {
        dashboardButton,
        gamingButton,
        processesButton,
        tweaksButton,
        logsButton
    };

    for (QPushButton* button : navButtons)
    {
        button->setMinimumHeight(
            46
        );

        sidebarLayout->addWidget(
            button
        );
    }

    // =========================================================
    // SIDEBAR SPACER
    // =========================================================

    sidebarLayout->addStretch();

    // =========================================================
    // SIDEBAR SYSTEM CARD
    // =========================================================

    QFrame* systemCard =
        new QFrame();

    systemCard->setObjectName(
        "systemCard"
    );

    QVBoxLayout* systemLayout =
        new QVBoxLayout(
            systemCard
        );

    systemLayout->setContentsMargins(
        14,
        13,
        14,
        13
    );

    systemLayout->setSpacing(
        7
    );

    QLabel* systemLabel =
        new QLabel(
            "SYSTEM"
        );

    systemLabel->setObjectName(
        "systemLabel"
    );

    QHBoxLayout* systemStatusLayout =
        new QHBoxLayout();

    systemStatusLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    systemStatusLayout->setSpacing(
        7
    );

    QLabel* statusDot =
        new QLabel(
            "●"
        );

    statusDot->setObjectName(
        "statusDot"
    );

    QLabel* statusText =
        new QLabel(
            "Monitoring active"
        );

    statusText->setObjectName(
        "statusText"
    );

    systemStatusLayout->addWidget(
        statusDot
    );

    systemStatusLayout->addWidget(
        statusText
    );

    systemStatusLayout->addStretch();

    QLabel* version =
        new QLabel(
            "CPC  •  v0.1.0"
        );

    version->setObjectName(
        "version"
    );

    systemLayout->addWidget(
        systemLabel
    );

    systemLayout->addLayout(
        systemStatusLayout
    );

    systemLayout->addWidget(
        version
    );

    sidebarLayout->addWidget(
        systemCard
    );

    // =========================================================
    // MAIN CONTENT
    // =========================================================

    QFrame* content =
        new QFrame();

    content->setObjectName(
        "content"
    );

    QVBoxLayout* contentLayout =
        new QVBoxLayout(
            content
        );

    contentLayout->setContentsMargins(
        32,
        26,
        32,
        30
    );

    contentLayout->setSpacing(
        22
    );

    // =========================================================
    // TOP HEADER
    // =========================================================

    QFrame* header =
        new QFrame();

    header->setObjectName(
        "header"
    );

    header->setFixedHeight(
        72
    );

    QHBoxLayout* headerLayout =
        new QHBoxLayout(
            header
        );

    headerLayout->setContentsMargins(
        20,
        0,
        12,
        0
    );

    // =========================================================
    // HEADER TITLE
    // =========================================================

    QVBoxLayout* titleLayout =
        new QVBoxLayout();

    titleLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    titleLayout->setSpacing(
        2
    );

    QLabel* title =
        new QLabel(
            "Dashboard"
        );

    title->setObjectName(
        "headerTitle"
    );

    QLabel* subtitle =
        new QLabel(
            "System performance at a glance"
        );

    subtitle->setObjectName(
        "headerSubtitle"
    );

    titleLayout->addWidget(
        title
    );

    titleLayout->addWidget(
        subtitle
    );

    headerLayout->addLayout(
        titleLayout
    );

    headerLayout->addStretch();

    // =========================================================
    // LIVE INDICATOR
    // =========================================================

    QFrame* liveContainer =
        new QFrame();

    liveContainer->setObjectName(
        "liveContainer"
    );

    liveContainer->setFixedHeight(
        38
    );

    QHBoxLayout* liveLayout =
        new QHBoxLayout(
            liveContainer
        );

    liveLayout->setContentsMargins(
        12,
        0,
        12,
        0
    );

    liveLayout->setSpacing(
        7
    );

    QLabel* liveDot =
        new QLabel(
            "●"
        );

    liveDot->setObjectName(
        "liveDot"
    );

    QLabel* liveText =
        new QLabel(
            "LIVE"
        );

    liveText->setObjectName(
        "liveText"
    );

    liveLayout->addWidget(
        liveDot
    );

    liveLayout->addWidget(
        liveText
    );

    headerLayout->addWidget(
        liveContainer
    );

    headerLayout->addSpacing(
        8
    );

    // =========================================================
    // THEME
    // =========================================================

    QPushButton* themeButton =
        new QPushButton(
            "☾"
        );

    themeButton->setObjectName(
        "themeButton"
    );

    themeButton->setCheckable(
        true
    );

    themeButton->setFixedSize(
        42,
        38
    );

    themeButton->setToolTip(
        "Toggle theme"
    );

    headerLayout->addWidget(
        themeButton
    );

    contentLayout->addWidget(
        header
    );

    // =========================================================
    // ACCENT LINE
    // =========================================================

    QFrame* accent =
        new QFrame();

    accent->setObjectName(
        "accent"
    );

    accent->setFixedHeight(
        2
    );

    contentLayout->addWidget(
        accent
    );

    // =========================================================
    // PAGE STACK
    // =========================================================

    QStackedWidget* pageStack =
        new QStackedWidget();

    pageStack->setObjectName(
        "pageStack"
    );

    // =========================================================
    // DASHBOARD
    // =========================================================

    Dashboard* dashboard =
        new Dashboard();

    pageStack->addWidget(
        dashboard
    );

    // =========================================================
    // GAMING MODE
    // =========================================================

    GamingMode* gamingMode =
        new GamingMode();

    pageStack->addWidget(
        gamingMode
    );

    // =========================================================
    // PROCESSES
    // =========================================================

    ProcessesPage* processesPage =
        new ProcessesPage();

    pageStack->addWidget(
        processesPage
    );

    contentLayout->addWidget(
        pageStack
    );

    // =========================================================
    // MAIN LAYOUT
    // =========================================================

    mainLayout->addWidget(
        sidebar
    );

    mainLayout->addWidget(
        content
    );

    // =========================================================
    // DARK THEME
    // =========================================================

    const QString darkTheme = R"(
        * {
            font-family: "Segoe UI";
        }

        QMainWindow,
        #central {
            background: #080a0f;
        }

        #content {
            background: #080a0f;
        }

        #sidebar {
            background: #0d1016;
            border-right: 1px solid #202530;
        }

        #brandContainer {
            background: transparent;
        }

        #brandMark {
            background: #5c7cff;
            border-radius: 9px;
        }

        #brandMarkText {
            color: white;
            font-size: 17px;
            font-weight: 900;
        }

        #brand {
            color: #f5f7fa;
            font-size: 18px;
            font-weight: 800;
            letter-spacing: 2px;
        }

        #brandSub {
            color: #596274;
            font-size: 8px;
            font-weight: 800;
            letter-spacing: 1.8px;
        }

        #navigationLabel {
            color: #4f5869;
            font-size: 9px;
            font-weight: 800;
            letter-spacing: 1.8px;
            padding-left: 10px;
        }

        #navButton,
        #navActive {
            border-radius: 9px;
            border: 1px solid transparent;
            text-align: left;
            padding-left: 15px;
            font-size: 13px;
            font-weight: 600;
        }

        #navButton {
            background: transparent;
            color: #737d8e;
        }

        #navButton:hover {
            background: #161a22;
            color: #e6e9ee;
            border: 1px solid #242a35;
        }

        #navActive {
            background: #171d2b;
            color: #ffffff;
            border: 1px solid #283652;
            border-left: 3px solid #6888ff;
        }

        #navButton:disabled {
            background: transparent;
            color: #454d5b;
            border: 1px solid transparent;
        }

        #systemCard {
            background: #11151d;
            border: 1px solid #222934;
            border-radius: 10px;
        }

        #systemLabel {
            color: #515c6f;
            font-size: 8px;
            font-weight: 800;
            letter-spacing: 1.6px;
        }

        #statusDot {
            color: #52dc8a;
            font-size: 9px;
        }

        #statusText {
            color: #a1a9b6;
            font-size: 11px;
            font-weight: 600;
        }

        #version {
            color: #555f70;
            font-size: 9px;
        }

        #header {
            background: #10141b;
            border: 1px solid #222832;
            border-radius: 13px;
        }

        #headerTitle {
            color: #f5f6f8;
            font-size: 22px;
            font-weight: 750;
        }

        #headerSubtitle {
            color: #697386;
            font-size: 11px;
        }

        #liveContainer {
            background: #101b17;
            border: 1px solid #1f3c30;
            border-radius: 8px;
        }

        #liveDot {
            color: #51db8a;
            font-size: 8px;
        }

        #liveText {
            color: #66c892;
            font-size: 9px;
            font-weight: 800;
            letter-spacing: 1.2px;
        }

        #themeButton {
            background: #171b23;
            color: #aab3c2;
            border: 1px solid #2b323e;
            border-radius: 8px;
            font-size: 18px;
            font-weight: 600;
        }

        #themeButton:hover {
            background: #222833;
            color: #ffffff;
            border: 1px solid #3b4657;
        }

        #themeButton:checked {
            background: #f0f2f5;
            color: #1a1d23;
            border: 1px solid #f0f2f5;
        }

        #accent {
            background: #5c7cff;
        }

        /* =====================================================
           PROCESS MANAGER - DARK
           ===================================================== */

        #processesPage {
            background: transparent;
        }

        #processManagerTitle {
            color: #f5f6f8;
            font-size: 19px;
            font-weight: 750;
        }

        #processCount {
            color: #687386;
            font-size: 11px;
            font-weight: 600;
        }

        #processSearch {
            background: #11161e;
            color: #e9edf3;
            border: 1px solid #29303c;
            border-radius: 8px;
            padding: 0 12px;
            min-height: 36px;
            selection-background-color: #5c7cff;
        }

        #processSearch:focus {
            border: 1px solid #5c7cff;
        }

        #processSearch::placeholder {
            color: #626c7c;
        }

        #processRefresh {
            background: #171d27;
            color: #dce1e9;
            border: 1px solid #2b3442;
            border-radius: 8px;
            min-height: 36px;
            font-weight: 600;
        }

        #processRefresh:hover {
            background: #202734;
            border: 1px solid #3a4658;
        }

        #processRefresh:pressed {
            background: #11151c;
        }

        #processTable {
            background: #0f131a;
            color: #dfe4ec;
            border: 1px solid #242b36;
            border-radius: 10px;
            gridline-color: transparent;
            outline: none;
        }

        #processTable QHeaderView::section {
            background: #151a22;
            color: #737e90;
            border: none;
            border-bottom: 1px solid #282f3b;
            padding: 0 10px;
            font-size: 10px;
            font-weight: 800;
        }

        #processTable QHeaderView::section:hover {
            background: #1b212b;
            color: #aab3c1;
        }

        #processTable::item {
            border: none;
            padding: 0 10px;
        }

        #processTable::item:selected {
            background: #1b2740;
            color: #ffffff;
        }

        #processTable::item:hover {
            background: #171e29;
        }

        #processTable QScrollBar:vertical {
            background: #0d1117;
            width: 10px;
            margin: 2px;
        }

        #processTable QScrollBar::handle:vertical {
            background: #303947;
            border-radius: 5px;
            min-height: 30px;
        }

        #processTable QScrollBar::handle:vertical:hover {
            background: #414d5e;
        }

        #processTable QScrollBar::add-line:vertical,
        #processTable QScrollBar::sub-line:vertical {
            height: 0;
        }

        #processTable QScrollBar:horizontal {
            background: #0d1117;
            height: 10px;
        }

        #processTable QScrollBar::handle:horizontal {
            background: #303947;
            border-radius: 5px;
        }

        #processTable QScrollBar::add-line:horizontal,
        #processTable QScrollBar::sub-line:horizontal {
            width: 0;
        }
    )";

    // =========================================================
    // LIGHT THEME
    // =========================================================

    const QString lightTheme = R"(
        * {
            font-family: "Segoe UI";
        }

        QMainWindow,
        #central {
            background: #f1f3f6;
        }

        #content {
            background: #f1f3f6;
        }

        #sidebar {
            background: #ffffff;
            border-right: 1px solid #dfe3e9;
        }

        #brandContainer {
            background: transparent;
        }

        #brandMark {
            background: #5273e8;
            border-radius: 9px;
        }

        #brandMarkText {
            color: white;
            font-size: 17px;
            font-weight: 900;
        }

        #brand {
            color: #171a20;
            font-size: 18px;
            font-weight: 800;
            letter-spacing: 2px;
        }

        #brandSub {
            color: #9299a5;
            font-size: 8px;
            font-weight: 800;
            letter-spacing: 1.8px;
        }

        #navigationLabel {
            color: #9ba2ad;
            font-size: 9px;
            font-weight: 800;
            letter-spacing: 1.8px;
            padding-left: 10px;
        }

        #navButton,
        #navActive {
            border-radius: 9px;
            border: 1px solid transparent;
            text-align: left;
            padding-left: 15px;
            font-size: 13px;
            font-weight: 600;
        }

        #navButton {
            background: transparent;
            color: #737b87;
        }

        #navButton:hover {
            background: #f0f2f5;
            color: #22262d;
            border: 1px solid #e0e3e8;
        }

        #navActive {
            background: #e9edfb;
            color: #3155ae;
            border: 1px solid #d5def6;
            border-left: 3px solid #5273e8;
        }

        #navButton:disabled {
            background: transparent;
            color: #b8bdc6;
            border: 1px solid transparent;
        }

        #systemCard {
            background: #f7f8fa;
            border: 1px solid #dfe3e9;
            border-radius: 10px;
        }

        #systemLabel {
            color: #969eaa;
            font-size: 8px;
            font-weight: 800;
            letter-spacing: 1.6px;
        }

        #statusDot {
            color: #35ad68;
            font-size: 9px;
        }

        #statusText {
            color: #59616e;
            font-size: 11px;
            font-weight: 600;
        }

        #version {
            color: #9aa1ab;
            font-size: 9px;
        }

        #header {
            background: #ffffff;
            border: 1px solid #dfe3e9;
            border-radius: 13px;
        }

        #headerTitle {
            color: #171a20;
            font-size: 22px;
            font-weight: 750;
        }

        #headerSubtitle {
            color: #858d99;
            font-size: 11px;
        }

        #liveContainer {
            background: #edf8f2;
            border: 1px solid #cde8d8;
            border-radius: 8px;
        }

        #liveDot {
            color: #35ad68;
            font-size: 8px;
        }

        #liveText {
            color: #378c5b;
            font-size: 9px;
            font-weight: 800;
            letter-spacing: 1.2px;
        }

        #themeButton {
            background: #ffffff;
            color: #646c78;
            border: 1px solid #d9dde4;
            border-radius: 8px;
            font-size: 18px;
            font-weight: 600;
        }

        #themeButton:hover {
            background: #eceff3;
            color: #20242b;
        }

        #themeButton:checked {
            background: #20242b;
            color: #ffffff;
            border: 1px solid #20242b;
        }

        #accent {
            background: #5273e8;
        }

        /* =====================================================
           PROCESS MANAGER - LIGHT
           ===================================================== */

        #processesPage {
            background: transparent;
        }

        #processManagerTitle {
            color: #171a20;
            font-size: 19px;
            font-weight: 750;
        }

        #processCount {
            color: #858d99;
            font-size: 11px;
            font-weight: 600;
        }

        #processSearch {
            background: #ffffff;
            color: #20242b;
            border: 1px solid #d8dde5;
            border-radius: 8px;
            padding: 0 12px;
            min-height: 36px;
            selection-background-color: #5273e8;
        }

        #processSearch:focus {
            border: 1px solid #5273e8;
        }

        #processSearch::placeholder {
            color: #9ba2ad;
        }

        #processRefresh {
            background: #ffffff;
            color: #4d5562;
            border: 1px solid #d8dde5;
            border-radius: 8px;
            min-height: 36px;
            font-weight: 600;
        }

        #processRefresh:hover {
            background: #f0f2f5;
            border: 1px solid #cbd1da;
        }

        #processRefresh:pressed {
            background: #e5e8ed;
        }

        #processTable {
            background: #ffffff;
            color: #252a32;
            border: 1px solid #dfe3e9;
            border-radius: 10px;
            gridline-color: transparent;
            outline: none;
        }

        #processTable QHeaderView::section {
            background: #f5f6f8;
            color: #777f8c;
            border: none;
            border-bottom: 1px solid #dfe3e9;
            padding: 0 10px;
            font-size: 10px;
            font-weight: 800;
        }

        #processTable QHeaderView::section:hover {
            background: #eceff3;
            color: #555d69;
        }

        #processTable::item {
            border: none;
            padding: 0 10px;
        }

        #processTable::item:selected {
            background: #e7ecfb;
            color: #203f8c;
        }

        #processTable::item:hover {
            background: #f3f5f8;
        }

        #processTable QScrollBar:vertical {
            background: #f1f3f6;
            width: 10px;
            margin: 2px;
        }

        #processTable QScrollBar::handle:vertical {
            background: #c7ccd5;
            border-radius: 5px;
            min-height: 30px;
        }

        #processTable QScrollBar::handle:vertical:hover {
            background: #adb4bf;
        }

        #processTable QScrollBar::add-line:vertical,
        #processTable QScrollBar::sub-line:vertical {
            height: 0;
        }

        #processTable QScrollBar:horizontal {
            background: #f1f3f6;
            height: 10px;
        }

        #processTable QScrollBar::handle:horizontal {
            background: #c7ccd5;
            border-radius: 5px;
        }

        #processTable QScrollBar::add-line:horizontal,
        #processTable QScrollBar::sub-line:horizontal {
            width: 0;
        }
    )";

    // =========================================================
    // APPLY INITIAL THEME
    // =========================================================

    setStyleSheet(
        darkTheme
    );

    // =========================================================
    // DASHBOARD NAVIGATION
    // =========================================================

    connect(
        dashboardButton,
        &QPushButton::clicked,
        this,
        [
            pageStack,
            dashboardButton,
            gamingButton,
            processesButton,
            title,
            subtitle
        ]()
        {
            pageStack->setCurrentIndex(0);

            dashboardButton->setObjectName(
                "navActive"
            );

            gamingButton->setObjectName(
                "navButton"
            );

            processesButton->setObjectName(
                "navButton"
            );

            title->setText(
                "Dashboard"
            );

            subtitle->setText(
                "System performance at a glance"
            );

            dashboardButton->style()->unpolish(
                dashboardButton
            );

            dashboardButton->style()->polish(
                dashboardButton
            );

            gamingButton->style()->unpolish(
                gamingButton
            );

            gamingButton->style()->polish(
                gamingButton
            );

            processesButton->style()->unpolish(
                processesButton
            );

            processesButton->style()->polish(
                processesButton
            );
        }
    );

    // =========================================================
    // GAMING MODE NAVIGATION
    // =========================================================

    connect(
        gamingButton,
        &QPushButton::clicked,
        this,
        [
            pageStack,
            dashboardButton,
            gamingButton,
            processesButton,
            title,
            subtitle
        ]()
        {
            pageStack->setCurrentIndex(1);

            dashboardButton->setObjectName(
                "navButton"
            );

            gamingButton->setObjectName(
                "navActive"
            );

            processesButton->setObjectName(
                "navButton"
            );

            title->setText(
                "Gaming Mode"
            );

            subtitle->setText(
                "Optimize Windows for gaming"
            );

            dashboardButton->style()->unpolish(
                dashboardButton
            );

            dashboardButton->style()->polish(
                dashboardButton
            );

            gamingButton->style()->unpolish(
                gamingButton
            );

            gamingButton->style()->polish(
                gamingButton
            );

            processesButton->style()->unpolish(
                processesButton
            );

            processesButton->style()->polish(
                processesButton
            );
        }
    );

    // =========================================================
    // PROCESSES NAVIGATION
    // =========================================================

    connect(
        processesButton,
        &QPushButton::clicked,
        this,
        [
            pageStack,
            dashboardButton,
            gamingButton,
            processesButton,
            title,
            subtitle
        ]()
        {
            pageStack->setCurrentIndex(2);

            dashboardButton->setObjectName(
                "navButton"
            );

            gamingButton->setObjectName(
                "navButton"
            );

            processesButton->setObjectName(
                "navActive"
            );

            title->setText(
                "Processes"
            );

            subtitle->setText(
                "Manage and monitor running processes"
            );

            dashboardButton->style()->unpolish(
                dashboardButton
            );

            dashboardButton->style()->polish(
                dashboardButton
            );

            gamingButton->style()->unpolish(
                gamingButton
            );

            gamingButton->style()->polish(
                gamingButton
            );

            processesButton->style()->unpolish(
                processesButton
            );

            processesButton->style()->polish(
                processesButton
            );
        }
    );

    // =========================================================
    // THEME TOGGLE
    // =========================================================

    connect(
        themeButton,
        &QPushButton::toggled,
        this,
        [
            this,
            themeButton,
            darkTheme,
            lightTheme
        ](bool lightMode)
        {
            if (lightMode)
            {
                themeButton->setText(
                    "☀"
                );

                setStyleSheet(
                    lightTheme
                );
            }
            else
            {
                themeButton->setText(
                    "☾"
                );

                setStyleSheet(
                    darkTheme
                );
            }
        }
    );
}