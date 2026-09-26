#include <QApplication>

#include "Monitoring/Monitoring.h"
#include "GPU/GPU.h"
#include "GUI/MainWindow.h"

int main(int argc, char* argv[])
{
    // =========================
    // APPLICATION
    // =========================

    QApplication app(argc, argv);

    QApplication::setApplicationName(
        "Cicitek Performance Center"
    );

    QApplication::setApplicationVersion(
        "0.1.0"
    );

    QApplication::setOrganizationName(
        "Cicitek Interactive"
    );


    // =========================
    // MONITORING
    // =========================

    // Inicializace celého monitorovacího systému
    Monitoring::Initialize();


    // =========================
    // GPU
    // =========================

    // GPU informace získáme pouze jednou
    std::string gpuName =
        GPU::GetName();

    unsigned long long vramBytes =
        GPU::GetVRAM();

    double vramGB =
        static_cast<double>(vramBytes) /
        (1024.0 * 1024.0 * 1024.0);


    // =========================
    // MAIN WINDOW
    // =========================

    MainWindow window;

    window.show();


    // =========================
    // APPLICATION LOOP
    // =========================

    return app.exec();
}