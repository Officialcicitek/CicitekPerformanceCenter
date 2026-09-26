#include "Disk.h"

#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>

#pragma comment(lib, "pdh.lib")

namespace Disk
{
    PDH_HQUERY query = nullptr;

    PDH_HCOUNTER readCounter = nullptr;
    PDH_HCOUNTER writeCounter = nullptr;

    void Initialize()
    {
        if (PdhOpenQueryW(
                nullptr,
                0,
                &query) != ERROR_SUCCESS)
        {
            query = nullptr;
            return;
        }

        if (PdhAddEnglishCounterW(
                query,
                L"\\PhysicalDisk(_Total)\\Disk Read Bytes/sec",
                0,
                &readCounter) != ERROR_SUCCESS)
        {
            PdhCloseQuery(query);
            query = nullptr;
            return;
        }

        if (PdhAddEnglishCounterW(
                query,
                L"\\PhysicalDisk(_Total)\\Disk Write Bytes/sec",
                0,
                &writeCounter) != ERROR_SUCCESS)
        {
            PdhCloseQuery(query);
            query = nullptr;
            return;
        }

        // První měření pouze inicializuje PDH.
        PdhCollectQueryData(query);
    }

    DiskUsage Update()
    {
        DiskUsage usage{};

        if (!query ||
            !readCounter ||
            !writeCounter)
        {
            return usage;
        }

        // PDH si mezi měřeními samo počítá Bytes/sec.
        if (PdhCollectQueryData(query) != ERROR_SUCCESS)
            return usage;

        PDH_FMT_COUNTERVALUE readValue{};

        if (PdhGetFormattedCounterValue(
                readCounter,
                PDH_FMT_DOUBLE,
                nullptr,
                &readValue) == ERROR_SUCCESS)
        {
            usage.readMBps =
                readValue.doubleValue /
                (1024.0 * 1024.0);
        }

        PDH_FMT_COUNTERVALUE writeValue{};

        if (PdhGetFormattedCounterValue(
                writeCounter,
                PDH_FMT_DOUBLE,
                nullptr,
                &writeValue) == ERROR_SUCCESS)
        {
            usage.writeMBps =
                writeValue.doubleValue /
                (1024.0 * 1024.0);
        }

        return usage;
    }
}