# Cicitek Performance Center

A modern native Windows performance monitoring and optimization application built with **C++20**, **Qt 6**, **WinAPI**, and **LibreHardwareMonitor**.

Cicitek Performance Center provides a clean real-time dashboard for monitoring PC hardware and system performance, together with system-level gaming optimizations.

## Features

### 📊 Hardware Monitoring

* 🖥️ CPU usage monitoring
* 🌡️ CPU temperature monitoring
* 🎮 GPU usage monitoring
* 🌡️ GPU temperature monitoring
* 💾 RAM usage and total memory
* 💽 Disk read/write activity
* 🌐 Network download/upload activity
* ⏱️ System uptime
* 📈 Real-time performance graphs
* 🎨 Dynamic temperature indicators

### 🎮 Gaming Mode

* ⚡ Gaming Mode activation and deactivation
* 🤖 Automatic Gaming Mode
* 🔍 Automatic game detection
* 🚀 Windows High Performance power plan switching
* 🔄 Automatic restoration of the previous power plan
* 🔥 High CPU Priority
* ♻️ Restoration of original process priorities
* 🧹 Background Optimization
* 🎯 Game Profile Manager
* 🎮 Multiple game detection
* 💾 Persistent Gaming Mode settings
* 📋 Active Windows power plan display

### 🎮 Supported Game Profiles

Currently included profiles:

* Roblox
* Counter-Strike 2
* VALORANT
* Fortnite
* League of Legends
* Minecraft
* Minecraft (Java)

### 🎨 User Interface

* 🌓 Dark and light UI themes
* 🖥️ Native Windows desktop interface
* 📱 Clean modular UI
* 📊 Real-time status indicators

## Technology

* **C++20**
* **Qt 6 Widgets**
* **CMake**
* **MSVC**
* **Windows API**
* **DXGI**
* **PDH**
* **WinHTTP**
* **Power Management API**
* **LibreHardwareMonitor**

## Architecture

The project is divided into separate modules for hardware monitoring, system management, gaming optimization, and the graphical interface.

```text
src/
├── CPU/
│   ├── CPU.h
│   └── CPU.cpp
├── RAM/
│   ├── RAM.h
│   └── RAM.cpp
├── GPU/
│   ├── GPU.h
│   └── GPU.cpp
├── Disk/
│   ├── Disk.h
│   └── Disk.cpp
├── Network/
│   ├── Network.h
│   └── Network.cpp
├── System/
│   ├── System.h
│   ├── System.cpp
│   ├── SettingsManager.h
│   └── SettingsManager.cpp
├── Monitoring/
│   ├── Monitoring.h
│   └── Monitoring.cpp
├── Temperature/
│   ├── Temperature.h
│   └── Temperature.cpp
├── GamingMode/
│   ├── GamingModeManager.h
│   ├── GamingModeManager.cpp
│   ├── BackgroundOptimizationManager.h
│   ├── BackgroundOptimizationManager.cpp
│   ├── GameProfileManager.h
│   └── GameProfileManager.cpp
└── GUI/
    ├── MainWindow.h
    ├── MainWindow.cpp
    ├── Dashboard/
    │   ├── Dashboard.h
    │   ├── Dashboard.cpp
    │   ├── LiveGraph.h
    │   └── LiveGraph.cpp
    └── GamingMode/
        ├── GamingMode.h
        └── GamingMode.cpp
```

This modular architecture allows the monitoring backend, system optimization, and graphical interface to evolve independently.

## Requirements

* Windows 10 or Windows 11
* Visual Studio with MSVC
* CMake
* Qt 6
* LibreHardwareMonitor

Qt is currently configured for:

```text
C:\Qt\6.11.2\msvc2022_64
```

## Building

Configure the project:

```powershell
cmake -S . -B build -G "Visual Studio 18 2026"
```

Build:

```powershell
cmake --build build --config Debug
```

Run:

```powershell
.\build\Debug\CicitekPerformanceCenter.exe
```

## LibreHardwareMonitor

Some temperature and GPU sensor information is provided through LibreHardwareMonitor's Remote Web Server.

The application currently communicates with the local monitoring service through:

```text
http://localhost:8085
```

Make sure the LibreHardwareMonitor Remote Web Server is running before launching the application.

## Gaming Mode

Gaming Mode integrates directly with Windows to apply performance-oriented system settings.

When enabled, the application can:

1. Switch Windows to the **High Performance** power plan.
2. Detect running games.
3. Apply configured game optimizations.
4. Increase the priority of supported game processes.
5. Reduce the priority of selected background applications.
6. Restore the previous system state when Gaming Mode is disabled.

Gaming Mode settings are stored persistently using Qt's `QSettings`.

## Game Profiles

Game profiles define optimization behavior for individual games.

Each profile can configure:

* Game name
* Process name
* High CPU Priority
* Background Optimization

The profile system is designed to make it possible to expand game-specific optimization without modifying the core Gaming Mode logic.

## Project Status

🚧 **Active development**

### v0.30 — Gaming Mode

The v0.30 update introduces the first complete Gaming Mode system, including:

* Automatic game detection
* Windows power plan management
* CPU process priority management
* Background process optimization
* Game profiles
* Persistent Gaming Mode settings
* Gaming Mode UI
* Dark/light theme support

### Next

The next development phase is focused on the **Processes** system.

Planned improvements include:

* Process listing
* CPU and RAM usage per process
* Process IDs
* Process priority information
* Process details
* Process management
* Improved process monitoring

Future monitoring improvements may also include:

* GPU hotspot monitoring
* VRAM used/total monitoring
* GPU and memory clock monitoring
* Additional hardware sensors
* More detailed monitoring views
* Performance history
* Improved hardware detection
* Release builds and packaging

## License

CicitekPerformanceCenter is licensed under the **Apache License 2.0**.

Copyright © 2026 cicitek.

See the [LICENSE](LICENSE) file for the full license text.

---

Made by **cicitek.interactive**
