#include "Network.h"

#include <windows.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

namespace Network
{
    struct NetworkStats
    {
        unsigned long long receivedBytes = 0;
        unsigned long long sentBytes = 0;
    };

    NetworkStats previousStats{};
    ULONGLONG previousTime = 0;

    NetworkStats GetStats()
    {
        NetworkStats stats{};

        ULONG size = 0;

        DWORD result =
            GetIfTable(
                nullptr,
                &size,
                FALSE
            );

        if (result != ERROR_INSUFFICIENT_BUFFER)
            return stats;

        auto* buffer = new BYTE[size];

        auto* table =
            reinterpret_cast<MIB_IFTABLE*>(buffer);

        result =
            GetIfTable(
                table,
                &size,
                FALSE
            );

        if (result != NO_ERROR)
        {
            delete[] buffer;
            return stats;
        }

        for (DWORD i = 0; i < table->dwNumEntries; ++i)
        {
            const MIB_IFROW& adapter =
                table->table[i];

            // Ignorujeme loopback adaptér.
            if (adapter.dwType == MIB_IF_TYPE_LOOPBACK)
                continue;

            // Pouze aktivní síťové adaptéry.
            if (adapter.dwOperStatus != IF_OPER_STATUS_OPERATIONAL)
                continue;

            stats.receivedBytes +=
                adapter.dwInOctets;

            stats.sentBytes +=
                adapter.dwOutOctets;
        }

        delete[] buffer;

        return stats;
    }

    void Initialize()
    {
        previousStats = GetStats();
        previousTime = GetTickCount64();
    }

    NetworkUsage Update()
    {
        NetworkUsage usage{};

        NetworkStats current =
            GetStats();

        ULONGLONG currentTime =
            GetTickCount64();

        double elapsedSeconds =
            static_cast<double>(
                currentTime - previousTime
            ) / 1000.0;

        if (elapsedSeconds <= 0.0)
            return usage;

        unsigned long long receivedBytes =
            current.receivedBytes -
            previousStats.receivedBytes;

        unsigned long long sentBytes =
            current.sentBytes -
            previousStats.sentBytes;

        usage.downloadMBps =
            static_cast<double>(receivedBytes) /
            elapsedSeconds /
            (1024.0 * 1024.0);

        usage.uploadMBps =
            static_cast<double>(sentBytes) /
            elapsedSeconds /
            (1024.0 * 1024.0);

        previousStats = current;
        previousTime = currentTime;

        return usage;
    }
}