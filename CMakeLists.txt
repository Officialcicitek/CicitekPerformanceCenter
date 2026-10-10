cmake_minimum_required(VERSION 3.20)

project(CicitekPerformanceCenter
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH
    "C:/Qt/6.11.2/msvc2022_64"
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)

add_executable(CicitekPerformanceCenter
    src/main.cpp

    src/GUI/MainWindow.cpp
    src/GUI/MainWindow.h

    src/GUI/Dashboard/Dashboard.cpp
    src/GUI/Dashboard/Dashboard.h
    src/GUI/Dashboard/LiveGraph.cpp
    src/GUI/Dashboard/LiveGraph.h

    src/GUI/GamingMode/GamingMode.cpp
    src/GUI/GamingMode/GamingMode.h

    src/GUI/Processes/Processes.cpp
    src/GUI/Processes/Processes.h

    src/GamingMode/GamingModeManager.cpp
    src/GamingMode/GamingModeManager.h
    src/GamingMode/BackgroundOptimizationManager.cpp
    src/GamingMode/BackgroundOptimizationManager.h
    src/GamingMode/GameProfileManager.cpp
    src/GamingMode/GameProfileManager.h

    src/System/SettingsManager.h
    src/System/SettingsManager.cpp

    src/CPU/CPU.cpp
    src/CPU/CPU.h
    src/RAM/RAM.cpp
    src/RAM/RAM.h
    src/System/System.cpp
    src/System/System.h
    src/GPU/GPU.cpp
    src/GPU/GPU.h
    src/Disk/Disk.cpp
    src/Disk/Disk.h
    src/Network/Network.cpp
    src/Network/Network.h
    src/Monitoring/Monitoring.cpp
    src/Monitoring/Monitoring.h
    src/Temperature/Temperature.cpp
    src/Temperature/Temperature.h

    src/Processes/Processes.cpp
    src/Processes/Processes.h
)

target_link_libraries(CicitekPerformanceCenter
    PRIVATE
    Qt6::Widgets
    Qt6::Concurrent
    Psapi
)