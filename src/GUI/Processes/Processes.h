#pragma once

#include <QWidget>

class QTableWidget;
class QLineEdit;
class QPushButton;
class QTimer;

class ProcessesPage : public QWidget
{
public:
    explicit ProcessesPage(QWidget* parent = nullptr);
    ~ProcessesPage() override = default;

private:
    QTableWidget* processTable = nullptr;
    QLineEdit* searchBox = nullptr;
    QPushButton* refreshButton = nullptr;
    QTimer* refreshTimer = nullptr;

    void refreshProcesses();
    void applySearchFilter();

    void showProcessContextMenu(
        const QPoint& position);
};