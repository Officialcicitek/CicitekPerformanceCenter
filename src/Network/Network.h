#pragma once

namespace Network
{
    struct NetworkUsage
    {
        double downloadMBps = 0.0;
        double uploadMBps = 0.0;
    };

    void Initialize();

    NetworkUsage Update();
}