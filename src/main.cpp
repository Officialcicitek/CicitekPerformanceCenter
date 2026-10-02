
#include <QApplication>

#include "GUI/MainWindow.h"

int main(int argc, char* argv[])
{
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


    // =========================================================
    // MAIN WINDOW
    // =========================================================

    MainWindow window;

    window.show();


    // =========================================================
    // APPLICATION LOOP
    // =========================================================

    return app.exec();
}
