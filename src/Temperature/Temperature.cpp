#include "Temperature.h"

#include <windows.h>
#include <winhttp.h>

#include <string>

#pragma comment(lib, "winhttp.lib")


namespace Temperature
{
    // =========================
    // SENSOR VALUE
    // =========================

    double GetSensorValue(
        const std::wstring& sensorId
    )
    {
        HINTERNET session =
            WinHttpOpen(
                L"CicitekPerformanceCenter/0.1",
                WINHTTP_ACCESS_TYPE_NO_PROXY,
                WINHTTP_NO_PROXY_NAME,
                WINHTTP_NO_PROXY_BYPASS,
                0
            );

        if (!session)
            return -1.0;


        HINTERNET connection =
            WinHttpConnect(
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


        std::wstring path =
            L"/Sensor?action=Get&id=" +
            sensorId;


        HINTERNET request =
            WinHttpOpenRequest(
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


        BOOL sent =
            WinHttpSendRequest(
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


        BOOL received =
            WinHttpReceiveResponse(
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


        while (
            WinHttpQueryDataAvailable(
                request,
                &availableSize
            )
            &&
            availableSize > 0
        )
        {
            std::string buffer(
                availableSize,
                '\0'
            );

            DWORD bytesRead = 0;


            if (!WinHttpReadData(
                    request,
                    buffer.data(),
                    availableSize,
                    &bytesRead
                ))
            {
                break;
            }


            buffer.resize(
                bytesRead
            );

            response += buffer;
        }


        WinHttpCloseHandle(request);
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);


        // =========================
        // PARSE VALUE
        // =========================

        const std::string key =
            "\"value\":";


        std::size_t position =
            response.find(key);


        if (position ==
            std::string::npos)
        {
            return -1.0;
        }


        position += key.length();


        std::size_t end =
            response.find(
                ',',
                position
            );


        if (end ==
            std::string::npos)
        {
            return -1.0;
        }


        std::string valueString =
            response.substr(
                position,
                end - position
            );


        try
        {
            return std::stod(
                valueString
            );
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
        return GetSensorValue(
            L"/amdcpu/0/temperature/2"
        );
    }


    // =========================
    // GPU TEMPERATURE
    // =========================

    double GetGPUTemperature()
    {
        return GetSensorValue(
            L"/gpu-nvidia/0/temperature/0"
        );
    }


    // =========================
    // GPU USAGE
    // =========================

    double GetGPUUsage()
    {
        return GetSensorValue(
            L"/gpu-nvidia/0/load/0"
        );
    }


    // =========================
    // GPU VRAM USED
    // =========================

    double GetGPUVRAMUsed()
    {
        return GetSensorValue(
            L"/gpu-nvidia/0/smalldata/1"
        );
    }
}