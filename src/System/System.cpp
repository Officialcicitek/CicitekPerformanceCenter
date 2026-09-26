#include "System.h"
#include <windows.h>

namespace System
{
    unsigned long long GetUptimeSeconds()
    {
        return GetTickCount64() / 1000;
    }
}