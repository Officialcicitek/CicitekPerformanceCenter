#pragma once

namespace Disk
{
    struct DiskUsage
    {
        double readMBps = 0.0;
        double writeMBps = 0.0;
    };

    void Initialize();

    DiskUsage Update();
}