// main.cpp
#include <QApplication>
#include "appcontroller.h" // Il nostro Controller principale

Q_DECLARE_METATYPE(Item*)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Inizializza l'applicazione Qt

    AppController controller; // Crea l'istanza del Controller.

    controller.start(); // Dici al Controller di avviare l'applicazione.

    return a.exec(); // Avvia il ciclo di eventi Qt.
}
