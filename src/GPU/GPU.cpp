#include "GPU.h"

#include <windows.h>
#include <dxgi.h>

#pragma comment(lib, "dxgi.lib")

namespace GPU
{
    std::string GetName()
    {
        IDXGIFactory* factory = nullptr;

        HRESULT result = CreateDXGIFactory(
            __uuidof(IDXGIFactory),
            reinterpret_cast<void**>(&factory)
        );

        if (FAILED(result))
            return "Unknown";

        IDXGIAdapter* adapter = nullptr;

        result = factory->EnumAdapters(0, &adapter);

        if (FAILED(result))
        {
            factory->Release();
            return "Unknown";
        }

        DXGI_ADAPTER_DESC desc{};

        result = adapter->GetDesc(&desc);

        if (FAILED(result))
        {
            adapter->Release();
            factory->Release();
            return "Unknown";
        }

        int size = WideCharToMultiByte(
            CP_UTF8,
            0,
            desc.Description,
            -1,
            nullptr,
            0,
            nullptr,
            nullptr
        );

        if (size <= 0)
        {
            adapter->Release();
            factory->Release();
            return "Unknown";
        }

        std::string name(size - 1, '\0');

        WideCharToMultiByte(
            CP_UTF8,
            0,
            desc.Description,
            -1,
            name.data(),
            size,
            nullptr,
            nullptr
        );

        adapter->Release();
        factory->Release();

        return name;
    }

    unsigned long long GetVRAM()
    {
        IDXGIFactory* factory = nullptr;

        HRESULT result = CreateDXGIFactory(
            __uuidof(IDXGIFactory),
            reinterpret_cast<void**>(&factory)
        );

        if (FAILED(result))
            return 0;

        IDXGIAdapter* adapter = nullptr;

        result = factory->EnumAdapters(0, &adapter);

        if (FAILED(result))
        {
            factory->Release();
            return 0;
        }

        DXGI_ADAPTER_DESC desc{};

        result = adapter->GetDesc(&desc);

        if (FAILED(result))
        {
            adapter->Release();
            factory->Release();
            return 0;
        }

        unsigned long long vram = desc.DedicatedVideoMemory;

        adapter->Release();
        factory->Release();

        return vram;
    }
}