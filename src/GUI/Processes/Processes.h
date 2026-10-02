#pragma once

#include <QWidget>

class QTableWidget;
class QLineEdit;
class QPushButton;

class ProcessesPage : public QWidget
{
public:
    explicit ProcessesPage(QWidget* parent = nullptr);

private:
    QTableWidget* processTable = nullptr;
    QLineEdit* searchBox = nullptr;
    QPushButton* refreshButton = nullptr;

    void refreshProcesses();
};