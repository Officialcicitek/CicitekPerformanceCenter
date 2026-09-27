#pragma once

#include <QWidget>

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

    QFrame* createCard(
        const QString& objectName,
        const QString& title,
        const QString& description
    );

    void applyTheme();

    QLabel* modeStatusLabel = nullptr;
    QLabel* detectedGameLabel = nullptr;
    QLabel* performanceProfileLabel = nullptr;

    QPushButton* modeToggleButton = nullptr;
};