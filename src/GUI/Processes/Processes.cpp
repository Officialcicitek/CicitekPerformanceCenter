#include "Processes.h"

#include "../../Processes/Processes.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

ProcessesPage::ProcessesPage(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->setContentsMargins(
        0,
        0,
        0,
        0
    );

    layout->setSpacing(16);


    // =========================================================
    // HEADER
    // =========================================================

    QHBoxLayout* topLayout = new QHBoxLayout();

    QLabel* title = new QLabel(
        "Running Processes"
    );

    title->setStyleSheet(
        "font-size: 20px; font-weight: 700;"
    );


    searchBox = new QLineEdit();

    searchBox->setPlaceholderText(
        "Search process..."
    );

    searchBox->setFixedWidth(
        230
    );


    refreshButton = new QPushButton(
        "Refresh"
    );

    refreshButton->setFixedWidth(
        90
    );


    topLayout->addWidget(
        title
    );

    topLayout->addStretch();

    topLayout->addWidget(
        searchBox
    );

    topLayout->addWidget(
        refreshButton
    );


    layout->addLayout(
        topLayout
    );


    // =========================================================
    // PROCESS TABLE
    // =========================================================

    processTable = new QTableWidget();

    processTable->setColumnCount(
        3
    );

    processTable->setHorizontalHeaderLabels(
        {
            "Process",
            "PID",
            "Memory"
        }
    );

    processTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    processTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    processTable->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    processTable->verticalHeader()->setVisible(
        false
    );

    processTable->horizontalHeader()->setStretchLastSection(
        true
    );

    processTable->setSortingEnabled(
        true
    );


    layout->addWidget(
        processTable
    );


    // =========================================================
    // CONNECTIONS
    // =========================================================

    connect(
        refreshButton,
        &QPushButton::clicked,
        this,
        &ProcessesPage::refreshProcesses
    );


    connect(
        searchBox,
        &QLineEdit::textChanged,
        this,
        [this](const QString& text)
        {
            for (int row = 0; row < processTable->rowCount(); ++row)
            {
                QTableWidgetItem* item =
                    processTable->item(row, 0);

                if (!item)
                {
                    continue;
                }

                bool visible =
                    item->text().contains(
                        text,
                        Qt::CaseInsensitive
                    );

                processTable->setRowHidden(
                    row,
                    !visible
                );
            }
        }
    );


    refreshProcesses();
}


// =========================================================
// REFRESH PROCESSES
// =========================================================

void ProcessesPage::refreshProcesses()
{
    processTable->setSortingEnabled(
        false
    );

    processTable->setRowCount(
        0
    );


    const QList<ProcessInfo> processes =
        Processes::getProcesses();


    for (const ProcessInfo& process : processes)
    {
        int row =
            processTable->rowCount();

        processTable->insertRow(
            row
        );


        QString memoryText;


        if (process.memoryUsage >= 1024ULL * 1024ULL * 1024ULL)
        {
            double gigabytes =
                static_cast<double>(
                    process.memoryUsage
                ) /
                (1024.0 * 1024.0 * 1024.0);

            memoryText =
                QString::number(
                    gigabytes,
                    'f',
                    2
                ) +
                " GB";
        }
        else
        {
            double megabytes =
                static_cast<double>(
                    process.memoryUsage
                ) /
                (1024.0 * 1024.0);

            memoryText =
                QString::number(
                    megabytes,
                    'f',
                    1
                ) +
                " MB";
        }


        processTable->setItem(
            row,
            0,
            new QTableWidgetItem(
                process.name
            )
        );


        processTable->setItem(
            row,
            1,
            new QTableWidgetItem(
                QString::number(
                    process.processId
                )
            )
        );


        processTable->setItem(
            row,
            2,
            new QTableWidgetItem(
                memoryText
            )
        );
    }


    processTable->resizeColumnsToContents();

    processTable->horizontalHeader()->setStretchLastSection(
        true
    );

    processTable->setSortingEnabled(
        true
    );
}