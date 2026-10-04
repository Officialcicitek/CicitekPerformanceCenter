#pragma once

#include <QString>
#include <QList>

struct ProcessInfo
{
    QString name;
    unsigned long processId = 0;
    unsigned long parentProcessId = 0;

    unsigned long long memoryUsage = 0;

    double cpuUsage = 0.0;

    unsigned long threadCount = 0;

    QString status;
    QString path;
};

class Processes
{
public:
    static QList<ProcessInfo> getProcesses();

    static bool terminateProcess(
        unsigned long processId);

    static bool terminateProcessTree(
        unsigned long processId);

    static bool openProcessLocation(
        const QString& path);
};