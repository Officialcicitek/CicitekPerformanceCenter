#include "Processes.h"

#include "../../Processes/Processes.h"

#include <windows.h>
#include <shellapi.h>

#include <QAction>
#include <QClipboard>
#include <QHash>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QIcon>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QSet>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTimer>
#include <QVBoxLayout>
#include <QApplication>

namespace
{
    QHash<QString, QIcon> processIconCache;

    QString formatMemory(
        unsigned long long bytes)
    {
        constexpr double KB = 1024.0;
        constexpr double MB = KB * 1024.0;
        constexpr double GB = MB * 1024.0;

        if (bytes >=
            static_cast<unsigned long long>(GB))
        {
            return QString::number(
                static_cast<double>(bytes) / GB,
                'f',
                2) + " GB";
        }

        if (bytes >=
            static_cast<unsigned long long>(MB))
        {
            return QString::number(
                static_cast<double>(bytes) / MB,
                'f',
                1) + " MB";
        }

        if (bytes >=
            static_cast<unsigned long long>(KB))
        {
            return QString::number(
                static_cast<double>(bytes) / KB,
                'f',
                1) + " KB";
        }

        return QString::number(bytes) + " B";
    }

    QTableWidgetItem* createItem(
        const QString& text)
    {
        QTableWidgetItem* item =
            new QTableWidgetItem(text);

        item->setFlags(
            item->flags() &
            ~Qt::ItemIsEditable);

        return item;
    }

    QIcon getProcessIcon(
        const QString& path)
    {
        if (path.isEmpty())
            return QIcon();

        const auto cached =
            processIconCache.constFind(path);

        if (cached !=
            processIconCache.constEnd())
        {
            return cached.value();
        }

        SHFILEINFOW fileInfo{};

        const std::wstring widePath =
            path.toStdWString();

        const DWORD result =
            SHGetFileInfoW(
                widePath.c_str(),
                0,
                &fileInfo,
                sizeof(fileInfo),
                SHGFI_ICON |
                SHGFI_SMALLICON);

        if (result == 0 ||
            !fileInfo.hIcon)
        {
            return QIcon();
        }

        QImage image =
            QImage::fromHICON(
                fileInfo.hIcon);

        DestroyIcon(
            fileInfo.hIcon);

        if (image.isNull())
        {
            return QIcon();
        }

        QIcon icon(
            QPixmap::fromImage(image));

        processIconCache.insert(
            path,
            icon);

        return icon;
    }
}

ProcessesPage::ProcessesPage(
    QWidget* parent)
    : QWidget(parent)
{
    setObjectName(
        "processesPage");

    QVBoxLayout* layout =
        new QVBoxLayout(this);

    layout->setContentsMargins(
        0,
        0,
        0,
        0);

    layout->setSpacing(16);

    // =========================================================
    // TOP BAR
    // =========================================================

    QHBoxLayout* topLayout =
        new QHBoxLayout();

    topLayout->setSpacing(10);

    QLabel* title =
        new QLabel(
            "Running Processes");

    title->setObjectName(
        "processManagerTitle");

    QLabel* processCount =
        new QLabel(
            "0 processes");

    processCount->setObjectName(
        "processCount");

    searchBox =
        new QLineEdit();

    searchBox->setObjectName(
        "processSearch");

    searchBox->setPlaceholderText(
        "Search processes...");

    searchBox->setClearButtonEnabled(
        true);

    searchBox->setFixedWidth(
        250);

    refreshButton =
        new QPushButton(
            "Refresh");

    refreshButton->setObjectName(
        "processRefresh");

    refreshButton->setCursor(
        Qt::PointingHandCursor);

    refreshButton->setFixedWidth(
        95);

    topLayout->addWidget(
        title);

    topLayout->addWidget(
        processCount);

    topLayout->addStretch();

    topLayout->addWidget(
        searchBox);

    topLayout->addWidget(
        refreshButton);

    layout->addLayout(
        topLayout);

    // =========================================================
    // PROCESS TABLE
    // =========================================================

    processTable =
        new QTableWidget();

    processTable->setObjectName(
        "processTable");

    processTable->setColumnCount(
        7);

    processTable->setHorizontalHeaderLabels(
        {
            "Process",
            "PID",
            "CPU",
            "Memory",
            "Threads",
            "Status",
            "Path"
        });

    processTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    processTable->setSelectionBehavior(
        QAbstractItemView::SelectRows);

    processTable->setSelectionMode(
        QAbstractItemView::SingleSelection);

    processTable->setFocusPolicy(
        Qt::NoFocus);

    processTable->setAlternatingRowColors(
        false);

    processTable->setShowGrid(
        false);

    processTable->verticalHeader()
        ->setVisible(false);

    processTable->verticalHeader()
        ->setDefaultSectionSize(
            38);

    processTable->horizontalHeader()
        ->setHighlightSections(
            false);

    processTable->horizontalHeader()
        ->setStretchLastSection(
            true);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            0,
            QHeaderView::Interactive);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            1,
            QHeaderView::ResizeToContents);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            2,
            QHeaderView::ResizeToContents);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            3,
            QHeaderView::ResizeToContents);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            4,
            QHeaderView::ResizeToContents);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            5,
            QHeaderView::ResizeToContents);

    processTable->horizontalHeader()
        ->setSectionResizeMode(
            6,
            QHeaderView::Stretch);

    processTable->setSortingEnabled(
        true);

    processTable->setWordWrap(
        false);

    // =========================================================
    // CONTEXT MENU
    // =========================================================

    processTable->setContextMenuPolicy(
        Qt::CustomContextMenu);

    connect(
        processTable,
        &QTableWidget::customContextMenuRequested,
        this,
        &ProcessesPage::showProcessContextMenu);

    layout->addWidget(
        processTable);

    // =========================================================
    // CONNECTIONS
    // =========================================================

    connect(
        refreshButton,
        &QPushButton::clicked,
        this,
        &ProcessesPage::refreshProcesses);

    connect(
        searchBox,
        &QLineEdit::textChanged,
        this,
        [this](const QString&)
        {
            applySearchFilter();
        });

    // =========================================================
    // AUTOMATIC REFRESH
    // =========================================================

    refreshTimer =
        new QTimer(this);

    refreshTimer->setInterval(
        5000);

    connect(
        refreshTimer,
        &QTimer::timeout,
        this,
        &ProcessesPage::refreshProcesses);

    refreshTimer->start();

    // =========================================================
    // INITIAL LOAD
    // =========================================================

    refreshProcesses();
}

// =============================================================
// REFRESH
// =============================================================

void ProcessesPage::refreshProcesses()
{
    if (!processTable)
        return;

    const QList<ProcessInfo> processes =
        Processes::getProcesses();

    const int sortColumn =
        processTable->horizontalHeader()
            ->sortIndicatorSection();

    const Qt::SortOrder sortOrder =
        processTable->horizontalHeader()
            ->sortIndicatorOrder();

    QHash<unsigned long, int> existingRows;

    for (int row = 0;
         row < processTable->rowCount();
         ++row)
    {
        QTableWidgetItem* pidItem =
            processTable->item(
                row,
                1);

        if (!pidItem)
            continue;

        bool ok = false;

        const unsigned long pid =
            pidItem->text()
                .toULong(&ok);

        if (ok && pid != 0)
        {
            existingRows.insert(
                pid,
                row);
        }
    }

    QSet<unsigned long> currentPids;

    int processCountValue = 0;

    bool rowsChanged = false;

    for (const ProcessInfo& process :
         processes)
    {
        currentPids.insert(
            process.processId);

        int row = -1;

        const auto existing =
            existingRows.constFind(
                process.processId);

        const bool isNewProcess =
            existing ==
            existingRows.constEnd();

        if (!isNewProcess)
        {
            row =
                existing.value();
        }
        else
        {
            row =
                processTable->rowCount();

            processTable->insertRow(
                row);

            rowsChanged = true;

            for (int column = 0;
                 column < 7;
                 ++column)
            {
                processTable->setItem(
                    row,
                    column,
                    createItem(""));
            }
        }

        // =====================================================
        // TEXT
        // =====================================================

        QTableWidgetItem* processItem =
            processTable->item(
                row,
                0);

        processItem->setText(
            process.name);

        // =====================================================
        // ICON
        // =====================================================

        if (isNewProcess &&
            !process.path.isEmpty())
        {
            const QIcon icon =
                getProcessIcon(
                    process.path);

            if (!icon.isNull())
            {
                processItem->setIcon(
                    icon);
            }
        }

        // =====================================================
        // PID
        // =====================================================

        QTableWidgetItem* pidItem =
            processTable->item(
                row,
                1);

        pidItem->setText(
            QString::number(
                process.processId));

        pidItem->setData(
            Qt::UserRole,
            static_cast<qulonglong>(
                process.processId));

        // =====================================================
        // CPU
        // =====================================================

        QTableWidgetItem* cpuItem =
            processTable->item(
                row,
                2);

        cpuItem->setText(
            QString::number(
                process.cpuUsage,
                'f',
                1) +
            " %");

        cpuItem->setData(
            Qt::UserRole,
            process.cpuUsage);

        // =====================================================
        // MEMORY
        // =====================================================

        QTableWidgetItem* memoryItem =
            processTable->item(
                row,
                3);

        memoryItem->setText(
            formatMemory(
                process.memoryUsage));

        memoryItem->setData(
            Qt::UserRole,
            static_cast<qulonglong>(
                process.memoryUsage));

        // =====================================================
        // THREADS
        // =====================================================

        QTableWidgetItem* threadItem =
            processTable->item(
                row,
                4);

        threadItem->setText(
            QString::number(
                process.threadCount));

        threadItem->setData(
            Qt::UserRole,
            static_cast<qulonglong>(
                process.threadCount));

        // =====================================================
        // STATUS
        // =====================================================

        QTableWidgetItem* statusItem =
            processTable->item(
                row,
                5);

        statusItem->setText(
            process.status);

        // =====================================================
        // PATH
        // =====================================================

        QTableWidgetItem* pathItem =
            processTable->item(
                row,
                6);

        QString path =
            process.path;

        if (path.isEmpty())
        {
            path =
                "Access denied";
        }

        pathItem->setText(
            path);

        ++processCountValue;
    }

    // =========================================================
    // REMOVE DEAD PROCESSES
    // =========================================================

    for (int row =
             processTable->rowCount() - 1;
         row >= 0;
         --row)
    {
        QTableWidgetItem* pidItem =
            processTable->item(
                row,
                1);

        if (!pidItem)
            continue;

        bool ok = false;

        const unsigned long pid =
            pidItem->text()
                .toULong(&ok);

        if (!ok ||
            !currentPids.contains(pid))
        {
            processTable->removeRow(
                row);

            rowsChanged = true;
        }
    }

    // =========================================================
    // SORT
    // =========================================================

    if (rowsChanged)
    {
        processTable->setSortingEnabled(
            false);

        if (sortColumn >= 0 &&
            sortColumn <
                processTable->columnCount())
        {
            processTable->sortItems(
                sortColumn,
                sortOrder);
        }

        processTable->setSortingEnabled(
            true);
    }

    // =========================================================
    // PROCESS COUNT
    // =========================================================

    QLabel* processCount =
        findChild<QLabel*>(
            "processCount");

    if (processCount)
    {
        processCount->setText(
            QString::number(
                processCountValue) +
            " processes");
    }

    applySearchFilter();
}

// =============================================================
// SEARCH
// =============================================================

void ProcessesPage::applySearchFilter()
{
    if (!processTable ||
        !searchBox)
    {
        return;
    }

    const QString search =
        searchBox->text()
            .trimmed();

    int visibleCount = 0;

    for (int row = 0;
         row < processTable->rowCount();
         ++row)
    {
        QTableWidgetItem* processItem =
            processTable->item(
                row,
                0);

        QTableWidgetItem* pidItem =
            processTable->item(
                row,
                1);

        QTableWidgetItem* pathItem =
            processTable->item(
                row,
                6);

        if (!processItem)
            continue;

        const bool matches =
            search.isEmpty() ||

            processItem->text()
                .contains(
                    search,
                    Qt::CaseInsensitive) ||

            (pidItem &&
             pidItem->text()
                 .contains(
                     search,
                     Qt::CaseInsensitive)) ||

            (pathItem &&
             pathItem->text()
                 .contains(
                     search,
                     Qt::CaseInsensitive));

        processTable->setRowHidden(
            row,
            !matches);

        if (matches)
        {
            ++visibleCount;
        }
    }

    QLabel* processCount =
        findChild<QLabel*>(
            "processCount");

    if (processCount)
    {
        processCount->setText(
            QString::number(
                visibleCount) +
            " processes");
    }
}

// =============================================================
// CONTEXT MENU
// =============================================================

void ProcessesPage::showProcessContextMenu(
    const QPoint& position)
{
    if (!processTable)
        return;

    QTableWidgetItem* item =
        processTable->itemAt(
            position);

    if (!item)
        return;

    const int row =
        item->row();

    processTable->selectRow(
        row);

    QTableWidgetItem* nameItem =
        processTable->item(
            row,
            0);

    QTableWidgetItem* pidItem =
        processTable->item(
            row,
            1);

    QTableWidgetItem* statusItem =
        processTable->item(
            row,
            5);

    QTableWidgetItem* pathItem =
        processTable->item(
            row,
            6);

    if (!pidItem)
        return;

    bool ok = false;

    const unsigned long processId =
        pidItem->text()
            .toULong(&ok);

    if (!ok ||
        processId == 0)
    {
        return;
    }

    const QString processName =
        nameItem
            ? nameItem->text()
            : QString("Process");

    const QString status =
        statusItem
            ? statusItem->text()
            : QString();

    const QString path =
        pathItem
            ? pathItem->text()
            : QString();

    QMenu menu(this);

    QAction* refreshAction =
        menu.addAction(
            "Refresh");

    menu.addSeparator();

    QAction* copyPidAction =
        menu.addAction(
            "Copy PID");

    QAction* copyPathAction =
        menu.addAction(
            "Copy path");

    menu.addSeparator();

    QAction* openLocationAction =
        menu.addAction(
            "Open file location");

    menu.addSeparator();

    QAction* endTaskAction =
        menu.addAction(
            "End Task");

    QAction* endTreeAction =
        menu.addAction(
            "End Process Tree");

    // =========================================================
    // PROTECTED PROCESS
    // =========================================================

    const bool protectedProcess =
        status == "Protected";

    if (protectedProcess)
    {
        endTaskAction->setEnabled(
            false);

        endTreeAction->setEnabled(
            false);

        endTaskAction->setToolTip(
            "Protected Windows process");

        endTreeAction->setToolTip(
            "Protected Windows process");
    }

    // =========================================================
    // ACCESS DENIED
    // =========================================================

    if (path.isEmpty() ||
        path == "Access denied")
    {
        openLocationAction->setEnabled(
            false);
    }

    QAction* selectedAction =
        menu.exec(
            processTable
                ->viewport()
                ->mapToGlobal(
                    position));

    // =========================================================
    // REFRESH
    // =========================================================

    if (selectedAction ==
        refreshAction)
    {
        refreshProcesses();
        return;
    }

    // =========================================================
    // COPY PID
    // =========================================================

    if (selectedAction ==
        copyPidAction)
    {
        QApplication::clipboard()
            ->setText(
                QString::number(
                    processId));

        return;
    }

    // =========================================================
    // COPY PATH
    // =========================================================

    if (selectedAction ==
        copyPathAction)
    {
        if (!path.isEmpty() &&
            path != "Access denied")
        {
            QApplication::clipboard()
                ->setText(path);
        }

        return;
    }

    // =========================================================
    // OPEN LOCATION
    // =========================================================

    if (selectedAction ==
        openLocationAction)
    {
        if (!Processes::openProcessLocation(
                path))
        {
            QMessageBox::warning(
                this,
                "Open file location",
                "Unable to open the process location.");
        }

        return;
    }

    // =========================================================
    // END TASK
    // =========================================================

    if (selectedAction ==
        endTaskAction)
    {
        const QMessageBox::StandardButton answer =
            QMessageBox::question(
                this,
                "End Task",
                QString(
                    "Do you really want to end \"%1\"?")
                    .arg(processName),
                QMessageBox::Yes |
                QMessageBox::No,
                QMessageBox::No);

        if (answer !=
            QMessageBox::Yes)
        {
            return;
        }

        if (!Processes::terminateProcess(
                processId))
        {
            QMessageBox::warning(
                this,
                "End Task",
                QString(
                    "Unable to end \"%1\".\n\n"
                    "The process may be protected "
                    "or require administrator privileges.")
                    .arg(processName));

            return;
        }

        refreshProcesses();
        return;
    }

    // =========================================================
    // END PROCESS TREE
    // =========================================================

    if (selectedAction ==
        endTreeAction)
    {
        const QMessageBox::StandardButton answer =
            QMessageBox::question(
                this,
                "End Process Tree",
                QString(
                    "Do you really want to end \"%1\" "
                    "and its child processes?")
                    .arg(processName),
                QMessageBox::Yes |
                QMessageBox::No,
                QMessageBox::No);

        if (answer !=
            QMessageBox::Yes)
        {
            return;
        }

        if (!Processes::terminateProcessTree(
                processId))
        {
            QMessageBox::warning(
                this,
                "End Process Tree",
                QString(
                    "Unable to end the process tree "
                    "for \"%1\".\n\n"
                    "Some processes may be protected "
                    "or require administrator privileges.")
                    .arg(processName));

            return;
        }

        refreshProcesses();
    }
}