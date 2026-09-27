#include "GamingMode.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QPushButton>
#include <QVBoxLayout>


GamingMode::GamingMode(QWidget* parent)
    : QWidget(parent)
{
    setObjectName("gamingMode");

    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    mainLayout->setSpacing(16);


    // =========================================================
    // PAGE HEADER
    // =========================================================

    QFrame* pageHeader =
        new QFrame();

    pageHeader->setObjectName(
        "gamingHeader"
    );

    QVBoxLayout* headerLayout =
        new QVBoxLayout(pageHeader);

    headerLayout->setContentsMargins(
        20,
        16,
        20,
        16
    );

    headerLayout->setSpacing(3);


    QLabel* title =
        new QLabel("Gaming Mode");

    title->setObjectName(
        "gamingPageTitle"
    );


    QLabel* subtitle =
        new QLabel(
            "Optimize your system for gaming"
        );

    subtitle->setObjectName(
        "gamingPageSubtitle"
    );


    headerLayout->addWidget(title);
    headerLayout->addWidget(subtitle);

    mainLayout->addWidget(
        pageHeader
    );


    // =========================================================
    // MAIN MODE CARD
    // =========================================================

    QFrame* modeCard =
        new QFrame();

    modeCard->setObjectName(
        "gamingModeCard"
    );

    QHBoxLayout* modeLayout =
        new QHBoxLayout(modeCard);

    modeLayout->setContentsMargins(
        22,
        20,
        22,
        20
    );

    modeLayout->setSpacing(18);


    // ---------------------------------------------------------
    // LEFT
    // ---------------------------------------------------------

    QVBoxLayout* modeTextLayout =
        new QVBoxLayout();

    modeTextLayout->setSpacing(4);


    QLabel* modeTitle =
        new QLabel("Gaming Mode");

    modeTitle->setObjectName(
        "gamingCardTitle"
    );


    modeStatusLabel =
        new QLabel("Inactive");

    modeStatusLabel->setObjectName(
        "gamingStatus"
    );


    QLabel* modeDescription =
        new QLabel(
            "Prioritize gaming performance and reduce background activity."
        );

    modeDescription->setObjectName(
        "gamingCardDescription"
    );

    modeDescription->setWordWrap(true);


    modeTextLayout->addWidget(
        modeTitle
    );

    modeTextLayout->addWidget(
        modeStatusLabel
    );

    modeTextLayout->addSpacing(4);

    modeTextLayout->addWidget(
        modeDescription
    );


    modeLayout->addLayout(
        modeTextLayout
    );

    modeLayout->addStretch();


    // ---------------------------------------------------------
    // TOGGLE
    // ---------------------------------------------------------

    modeToggleButton =
        new QPushButton("ENABLE");

    modeToggleButton->setObjectName(
        "gamingToggle"
    );

    modeToggleButton->setCheckable(true);

    modeToggleButton->setFixedSize(
        120,
        42
    );


    modeLayout->addWidget(
        modeToggleButton
    );


    connect(
        modeToggleButton,
        &QPushButton::toggled,
        this,
        [this](bool enabled)
        {
            if (enabled)
            {
                modeToggleButton->setText(
                    "ACTIVE"
                );

                modeStatusLabel->setText(
                    "Gaming Mode Active"
                );

                modeStatusLabel->setProperty(
                    "active",
                    true
                );
            }
            else
            {
                modeToggleButton->setText(
                    "ENABLE"
                );

                modeStatusLabel->setText(
                    "Inactive"
                );

                modeStatusLabel->setProperty(
                    "active",
                    false
                );
            }

            modeStatusLabel->style()->unpolish(
                modeStatusLabel
            );

            modeStatusLabel->style()->polish(
                modeStatusLabel
            );

            modeStatusLabel->update();
        }
    );


    mainLayout->addWidget(
        modeCard
    );


    // =========================================================
    // STATUS CARDS
    // =========================================================

    QHBoxLayout* statusLayout =
        new QHBoxLayout();

    statusLayout->setSpacing(16);


    // ---------------------------------------------------------
    // GAME DETECTION
    // ---------------------------------------------------------

    QFrame* gameCard =
        createCard(
            "gameDetectionCard",
            "GAME DETECTION",
            "Automatically detect when a game is running."
        );


    QVBoxLayout* gameLayout =
        qobject_cast<QVBoxLayout*>(
            gameCard->layout()
        );


    detectedGameLabel =
        new QLabel("No game detected");

    detectedGameLabel->setObjectName(
        "gamingValue"
    );

    gameLayout->addWidget(
        detectedGameLabel
    );


    statusLayout->addWidget(
        gameCard
    );


    // ---------------------------------------------------------
    // PERFORMANCE PROFILE
    // ---------------------------------------------------------

    QFrame* profileCard =
        createCard(
            "performanceProfileCard",
            "PERFORMANCE PROFILE",
            "Current system performance profile."
        );


    QVBoxLayout* profileLayout =
        qobject_cast<QVBoxLayout*>(
            profileCard->layout()
        );


    performanceProfileLabel =
        new QLabel("Balanced");

    performanceProfileLabel->setObjectName(
        "gamingValue"
    );

    profileLayout->addWidget(
        performanceProfileLabel
    );


    statusLayout->addWidget(
        profileCard
    );


    mainLayout->addLayout(
        statusLayout
    );


    // =========================================================
    // SETTINGS
    // =========================================================

    QFrame* settingsCard =
        new QFrame();

    settingsCard->setObjectName(
        "gamingSettingsCard"
    );


    QVBoxLayout* settingsLayout =
        new QVBoxLayout(settingsCard);

    settingsLayout->setContentsMargins(
        20,
        18,
        20,
        18
    );

    settingsLayout->setSpacing(14);


    QLabel* settingsTitle =
        new QLabel("Gaming Settings");

    settingsTitle->setObjectName(
        "gamingSectionTitle"
    );


    settingsLayout->addWidget(
        settingsTitle
    );


    // ---------------------------------------------------------
    // OPTION 1
    // ---------------------------------------------------------

    QFrame* priorityRow =
        new QFrame();

    priorityRow->setObjectName(
        "gamingSettingRow"
    );


    QHBoxLayout* priorityLayout =
        new QHBoxLayout(priorityRow);

    priorityLayout->setContentsMargins(
        14,
        10,
        14,
        10
    );


    QLabel* priorityText =
        new QLabel(
            "High CPU priority"
        );

    priorityText->setObjectName(
        "gamingSettingTitle"
    );


    QLabel* priorityDescription =
        new QLabel(
            "Prioritize the active game process."
        );

    priorityDescription->setObjectName(
        "gamingSettingDescription"
    );


    QVBoxLayout* priorityTextLayout =
        new QVBoxLayout();

    priorityTextLayout->setSpacing(2);

    priorityTextLayout->addWidget(
        priorityText
    );

    priorityTextLayout->addWidget(
        priorityDescription
    );


    QPushButton* priorityButton =
        new QPushButton("OFF");

    priorityButton->setCheckable(true);

    priorityButton->setObjectName(
        "gamingOptionButton"
    );

    priorityButton->setFixedSize(
        72,
        32
    );


    connect(
        priorityButton,
        &QPushButton::toggled,
        this,
        [priorityButton](bool enabled)
        {
            priorityButton->setText(
                enabled ? "ON" : "OFF"
            );
        }
    );


    priorityLayout->addLayout(
        priorityTextLayout
    );

    priorityLayout->addStretch();

    priorityLayout->addWidget(
        priorityButton
    );


    settingsLayout->addWidget(
        priorityRow
    );


    // ---------------------------------------------------------
    // OPTION 2
    // ---------------------------------------------------------

    QFrame* backgroundRow =
        new QFrame();

    backgroundRow->setObjectName(
        "gamingSettingRow"
    );


    QHBoxLayout* backgroundLayout =
        new QHBoxLayout(backgroundRow);

    backgroundLayout->setContentsMargins(
        14,
        10,
        14,
        10
    );


    QLabel* backgroundText =
        new QLabel(
            "Background optimization"
        );

    backgroundText->setObjectName(
        "gamingSettingTitle"
    );


    QLabel* backgroundDescription =
        new QLabel(
            "Reduce unnecessary background activity."
        );

    backgroundDescription->setObjectName(
        "gamingSettingDescription"
    );


    QVBoxLayout* backgroundTextLayout =
        new QVBoxLayout();

    backgroundTextLayout->setSpacing(2);

    backgroundTextLayout->addWidget(
        backgroundText
    );

    backgroundTextLayout->addWidget(
        backgroundDescription
    );


    QPushButton* backgroundButton =
        new QPushButton("OFF");

    backgroundButton->setCheckable(true);

    backgroundButton->setObjectName(
        "gamingOptionButton"
    );

    backgroundButton->setFixedSize(
        72,
        32
    );


    connect(
        backgroundButton,
        &QPushButton::toggled,
        this,
        [backgroundButton](bool enabled)
        {
            backgroundButton->setText(
                enabled ? "ON" : "OFF"
            );
        }
    );


    backgroundLayout->addLayout(
        backgroundTextLayout
    );

    backgroundLayout->addStretch();

    backgroundLayout->addWidget(
        backgroundButton
    );


    settingsLayout->addWidget(
        backgroundRow
    );


    mainLayout->addWidget(
        settingsCard
    );


    mainLayout->addStretch();


    // =========================================================
    // INITIAL THEME
    // =========================================================

    setLightMode(false);
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
        18,
        16,
        18,
        16
    );

    layout->setSpacing(5);


    QLabel* titleLabel =
        new QLabel(title);

    titleLabel->setObjectName(
        "gamingSmallTitle"
    );


    QLabel* descriptionLabel =
        new QLabel(description);

    descriptionLabel->setObjectName(
        "gamingSmallDescription"
    );

    descriptionLabel->setWordWrap(true);


    layout->addWidget(
        titleLabel
    );

    layout->addWidget(
        descriptionLabel
    );


    return card;
}


// =============================================================
// THEME
// =============================================================

void GamingMode::setLightMode(
    bool lightMode
)
{
    m_lightMode = lightMode;

    applyTheme();
}


// =============================================================
// APPLY THEME
// =============================================================

void GamingMode::applyTheme()
{
    if (m_lightMode)
    {
        setStyleSheet(R"(

            #gamingHeader,
            #gamingModeCard,
            #gameDetectionCard,
            #performanceProfileCard,
            #gamingSettingsCard {
                background: #ffffff;
                border: 1px solid #dfe3e9;
                border-radius: 13px;
            }

            #gamingPageTitle {
                color: #20242b;
                font-size: 22px;
                font-weight: 750;
            }

            #gamingPageSubtitle {
                color: #858d99;
                font-size: 11px;
            }

            #gamingCardTitle {
                color: #333943;
                font-size: 15px;
                font-weight: 700;
            }

            #gamingStatus {
                color: #8a929d;
                font-size: 11px;
                font-weight: 700;
            }

            #gamingStatus[active="true"] {
                color: #35ad68;
            }

            #gamingCardDescription,
            #gamingSmallDescription,
            #gamingSettingDescription {
                color: #858d99;
                font-size: 10px;
            }

            #gamingToggle {
                background: #5273e8;
                color: white;
                border: none;
                border-radius: 8px;
                font-size: 10px;
                font-weight: 800;
            }

            #gamingToggle:hover {
                background: #4567dc;
            }

            #gamingToggle:checked {
                background: #35ad68;
            }

            #gamingSmallTitle,
            #gamingSectionTitle {
                color: #737c89;
                font-size: 9px;
                font-weight: 800;
                letter-spacing: 1.3px;
            }

            #gamingValue {
                color: #20242b;
                font-size: 18px;
                font-weight: 700;
            }

            #gamingSettingRow {
                background: #f7f8fa;
                border: 1px solid #e1e5ea;
                border-radius: 9px;
            }

            #gamingSettingTitle {
                color: #333943;
                font-size: 12px;
                font-weight: 650;
            }

            #gamingOptionButton {
                background: #e9edf2;
                color: #626b77;
                border: 1px solid #d9dee5;
                border-radius: 7px;
                font-size: 9px;
                font-weight: 800;
            }

            #gamingOptionButton:checked {
                background: #5273e8;
                color: white;
                border: 1px solid #5273e8;
            }

        )");
    }
    else
    {
        setStyleSheet(R"(

            #gamingHeader,
            #gamingModeCard,
            #gameDetectionCard,
            #performanceProfileCard,
            #gamingSettingsCard {
                background: #10141b;
                border: 1px solid #222832;
                border-radius: 13px;
            }

            #gamingPageTitle {
                color: #f0f2f6;
                font-size: 22px;
                font-weight: 750;
            }

            #gamingPageSubtitle {
                color: #697386;
                font-size: 11px;
            }

            #gamingCardTitle {
                color: #e1e5eb;
                font-size: 15px;
                font-weight: 700;
            }

            #gamingStatus {
                color: #737d8e;
                font-size: 11px;
                font-weight: 700;
            }

            #gamingStatus[active="true"] {
                color: #51db8a;
            }

            #gamingCardDescription,
            #gamingSmallDescription,
            #gamingSettingDescription {
                color: #697386;
                font-size: 10px;
            }

            #gamingToggle {
                background: #5c7cff;
                color: white;
                border: none;
                border-radius: 8px;
                font-size: 10px;
                font-weight: 800;
            }

            #gamingToggle:hover {
                background: #6d8aff;
            }

            #gamingToggle:checked {
                background: #35c77d;
            }

            #gamingSmallTitle,
            #gamingSectionTitle {
                color: #697386;
                font-size: 9px;
                font-weight: 800;
                letter-spacing: 1.3px;
            }

            #gamingValue {
                color: #f0f2f6;
                font-size: 18px;
                font-weight: 700;
            }

            #gamingSettingRow {
                background: #151a22;
                border: 1px solid #252c36;
                border-radius: 9px;
            }

            #gamingSettingTitle {
                color: #dce1e8;
                font-size: 12px;
                font-weight: 650;
            }

            #gamingOptionButton {
                background: #1d232d;
                color: #8b95a4;
                border: 1px solid #2c3440;
                border-radius: 7px;
                font-size: 9px;
                font-weight: 800;
            }

            #gamingOptionButton:checked {
                background: #5c7cff;
                color: white;
                border: 1px solid #5c7cff;
            }

        )");
    }
}