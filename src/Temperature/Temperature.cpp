
#include "Temperature.h"

#include <windows.h>
#include <winhttp.h>

#include <string>
#include <algorithm>
#include <cwctype>
#include <cctype>

#pragma comment(lib, "winhttp.lib")

namespace Temperature
{
    // =========================
    // SENSOR VALUE
    // =========================

    double GetSensorValue(const std::wstring& sensorId)
    {
        HINTERNET session = WinHttpOpen(
            L"CicitekPerformanceCenter/0.4.0",
            WINHTTP_ACCESS_TYPE_NO_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0
        );

        if (!session)
            return -1.0;

        // Keep failed sensor requests from waiting for several seconds.
        WinHttpSetTimeouts(
            session,
            200,  // Resolve timeout
            200,  // Connect timeout
            200,  // Send timeout
            200   // Receive timeout
        );

        HINTERNET connection = WinHttpConnect(
            session,
            L"localhost",
            8085,
            0
        );

        if (!connection)
        {
            WinHttpCloseHandle(session);
            return -1.0;
        }

        const std::wstring path =
            L"/Sensor?action=Get&id=" + sensorId;

        HINTERNET request = WinHttpOpenRequest(
            connection,
            L"GET",
            path.c_str(),
            nullptr,
            WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            0
        );

        if (!request)
        {
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(session);
            return -1.0;
        }

        const BOOL sent = WinHttpSendRequest(
            request,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0,
            WINHTTP_NO_REQUEST_DATA,
            0,
            0,
            0
        );

        if (!sent)
        {
            WinHttpCloseHandle(request);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(session);
            return -1.0;
        }

        const BOOL received = WinHttpReceiveResponse(
            request,
            nullptr
        );

        if (!received)
        {
            WinHttpCloseHandle(request);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(session);
            return -1.0;
        }

        std::string response;
        DWORD availableSize = 0;

        while (WinHttpQueryDataAvailable(request, &availableSize)
               && availableSize > 0)
        {
            std::string buffer(availableSize, '\0');
            DWORD bytesRead = 0;

            if (!WinHttpReadData(
                    request,
                    buffer.data(),
                    availableSize,
                    &bytesRead))
            {
                break;
            }

            if (bytesRead == 0)
                break;

            buffer.resize(bytesRead);
            response += buffer;
        }

        WinHttpCloseHandle(request);
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);

        // =========================
        // PARSE JSON VALUE
        // =========================

        const std::string key = "\"value\"";

        std::size_t position = response.find(key);

        if (position == std::string::npos)
            return -1.0;

        position += key.length();

        // Find the colon after "value".
        position = response.find(':', position);

        if (position == std::string::npos)
            return -1.0;

        ++position;

        // Skip whitespace.
        while (position < response.size()
               && std::isspace(
                   static_cast<unsigned char>(response[position])))
        {
            ++position;
        }

        // JSON values can end with either ',' or '}'.
        std::size_t end = response.find_first_of(",}", position);

        if (end == std::string::npos)
            end = response.size();

        std::string valueString =
            response.substr(position, end - position);

        try
        {
            std::size_t parsed = 0;
            const double value = std::stod(valueString, &parsed);

            if (parsed == 0)
                return -1.0;

            return value;
        }
        catch (...)
        {
            return -1.0;
        }
    }

    // =========================
    // CPU TEMPERATURE
    // =========================

    double GetCPUTemperature()
    {
        return GetSensorValue(L"/amdcpu/0/temperature/2");
    }

    // =========================
    // GPU TEMPERATURE
    // =========================

    double GetGPUTemperature()
    {
        return GetSensorValue(L"/gpu-nvidia/0/temperature/0");
    }

    // =========================
    // GPU HOTSPOT
    // =========================

    double GetGPUHotspot()
    {
        return GetSensorValue(L"/gpu-nvidia/0/temperature/2");
    }

    // =========================
    // GPU USAGE
    // =========================

    double GetGPUUsage()
    {
        return GetSensorValue(L"/gpu-nvidia/0/load/0");
    }

    // =========================
    // GPU VRAM USED
    // =========================

    double GetGPUVRAMUsed()
    {
        return GetSensorValue(L"/gpu-nvidia/0/smalldata/1");
    }

    // =========================
    // GPU VRAM TOTAL
    // =========================

    double GetGPUVRAMTotal()
    {
        return GetSensorValue(L"/gpu-nvidia/0/smalldata/2");
    }
}
