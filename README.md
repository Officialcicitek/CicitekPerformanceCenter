# Cicitek Performance Center

A modern native Windows performance monitoring application built with **C++20**, **Qt 6**, **WinAPI**, and **LibreHardwareMonitor**.

Cicitek Performance Center provides a clean real-time dashboard for monitoring PC hardware and system performance without relying on a web-based interface.

## Features

* 🖥️ CPU usage monitoring
* 🌡️ CPU temperature monitoring
* 🎮 GPU usage monitoring
* 🌡️ GPU temperature monitoring
* 💾 RAM usage and total memory
* 📊 Real-time performance graphs
* 💽 Disk read/write activity
* 🌐 Network download/upload activity
* ⏱️ System uptime
* 🎨 Dynamic temperature indicators
* 🌓 Dark and light UI themes
* 🖥️ Native Windows desktop interface

## Technology

* **C++20**
* **Qt 6 Widgets**
* **CMake**
* **MSVC**
* **Windows API**
* **DXGI**
* **PDH**
* **WinHTTP**
* **LibreHardwareMonitor**

## Architecture

The project is split into separate modules for hardware monitoring and the graphical interface.

```text
src/
├── CPU/
├── RAM/
├── GPU/
├── Disk/
├── Network/
├── System/
├── Monitoring/
├── Temperature/
└── GUI/
    ├── MainWindow
    └── Dashboard/
```

This separation allows the monitoring backend and graphical interface to evolve independently.

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

## Project Status

🚧 **Active development**

The current version focuses on the core monitoring dashboard and a polished native Windows UI.

Planned improvements include:

* GPU hotspot monitoring
* VRAM used/total monitoring
* GPU and memory clock monitoring
* Additional hardware sensors
* More detailed monitoring views
* Performance history
* Improved hardware detection
* Release builds and packaging

## License

License information will be added before the first public release.

---

Made by **cicitek.interactive**
