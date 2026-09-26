#include "CPU.h"

#include <windows.h>

namespace CPU
{
    ULONGLONG previousIdle = 0;
    ULONGLONG previousKernel = 0;
    ULONGLONG previousUser = 0;

    void Initialize()
    {
        FILETIME idleTime, kernelTime, userTime;

        if (!GetSystemTimes(
                &idleTime,
                &kernelTime,
                &userTime))
        {
            return;
        }

        ULARGE_INTEGER idle;
        ULARGE_INTEGER kernel;
        ULARGE_INTEGER user;

        idle.LowPart = idleTime.dwLowDateTime;
        idle.HighPart = idleTime.dwHighDateTime;

        kernel.LowPart = kernelTime.dwLowDateTime;
        kernel.HighPart = kernelTime.dwHighDateTime;

        user.LowPart = userTime.dwLowDateTime;
        user.HighPart = userTime.dwHighDateTime;

        previousIdle = idle.QuadPart;
        previousKernel = kernel.QuadPart;
        previousUser = user.QuadPart;
    }

    double GetUsage()
    {
        FILETIME idleTime, kernelTime, userTime;

        if (!GetSystemTimes(
                &idleTime,
                &kernelTime,
                &userTime))
        {
            return -1.0;
        }

        ULARGE_INTEGER idle;
        ULARGE_INTEGER kernel;
        ULARGE_INTEGER user;

        idle.LowPart = idleTime.dwLowDateTime;
        idle.HighPart = idleTime.dwHighDateTime;

        kernel.LowPart = kernelTime.dwLowDateTime;
        kernel.HighPart = kernelTime.dwHighDateTime;

        user.LowPart = userTime.dwLowDateTime;
        user.HighPart = userTime.dwHighDateTime;

        ULONGLONG currentIdle = idle.QuadPart;
        ULONGLONG currentKernel = kernel.QuadPart;
        ULONGLONG currentUser = user.QuadPart;

        ULONGLONG idleDelta =
            currentIdle - previousIdle;

        ULONGLONG kernelDelta =
            currentKernel - previousKernel;

        ULONGLONG userDelta =
            currentUser - previousUser;

        ULONGLONG totalDelta =
            kernelDelta + userDelta;

        previousIdle = currentIdle;
        previousKernel = currentKernel;
        previousUser = currentUser;

        if (totalDelta == 0)
            return 0.0;

        return 100.0 *
            static_cast<double>(
                totalDelta - idleDelta
            ) /
            static_cast<double>(totalDelta);
    }
}