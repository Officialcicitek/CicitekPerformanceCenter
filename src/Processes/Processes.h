#pragma once

#include <QString>
#include <QList>

struct ProcessInfo
{
    QString name;
    unsigned long processId;
    unsigned long long memoryUsage;
};

class Processes
{
public:
    static QList<ProcessInfo> getProcesses();
};