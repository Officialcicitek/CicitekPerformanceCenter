#include "System.h"

#include <windows.h>

#include <string>

#pragma comment(lib, "Advapi32.lib")

namespace System
{
    unsigned long long GetUptimeSeconds()
    {
        return GetTickCount64() / 1000ULL;
    }


    const char* GetCPUName()
    {
        static std::string cpuName;

        if (!cpuName.empty())
        {
            return cpuName.c_str();
        }


        HKEY key = nullptr;


        const LONG result =
            RegOpenKeyExA(
                HKEY_LOCAL_MACHINE,
                "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                0,
                KEY_READ,
                &key
            );


        if (result != ERROR_SUCCESS)
        {
            cpuName = "Unknown CPU";

            return cpuName.c_str();
        }


        char buffer[256] = {};

        DWORD bufferSize =
            sizeof(buffer);

        DWORD type = 0;


        const LONG valueResult =
            RegQueryValueExA(
                key,
                "ProcessorNameString",
                nullptr,
                &type,
                reinterpret_cast<LPBYTE>(buffer),
                &bufferSize
            );


        RegCloseKey(
            key
        );


        if (
            valueResult != ERROR_SUCCESS ||
            buffer[0] == '\0'
        )
        {
            cpuName = "Unknown CPU";

            return cpuName.c_str();
        }


        cpuName =
            buffer;


        // Odstranění mezer na začátku.
        while (
            !cpuName.empty() &&
            cpuName.front() == ' '
        )
        {
            cpuName.erase(
                cpuName.begin()
            );
        }


        // Odstranění mezer na konci.
        while (
            !cpuName.empty() &&
            cpuName.back() == ' '
        )
        {
            cpuName.pop_back();
        }


        return cpuName.c_str();
    }
}