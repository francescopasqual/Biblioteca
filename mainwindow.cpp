// mainwindow.cpp
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. Crea lo QStackedWidget
    stackedWidget = new QStackedWidget(this); // Passa 'this' (la MainWindow) come parent

    // 2. Imposta lo QStackedWidget come widget centrale della MainWindow
    setCentralWidget(stackedWidget);

    // Non creiamo le schermate specifiche (LoginScreen, CatalogScreen) qui.
    // Sarà il Controller a crearle e aggiungerle allo stackedWidget.

    // Puoi impostare qui proprietà della finestra principale come il titolo iniziale, le dimensioni, ecc.
    setWindowTitle("La Mia Biblioteca");
    resize(800, 600); // Dimensione iniziale
}

MainWindow::~MainWindow()
{
    // Lo stackedWidget è un figlio QObject (parent è 'this'), verrà distrutto automaticamente.
    // Non deallocare qui stackedWidget se l'hai creato con 'this' come parent.
}

// Implementazione del metodo per ottenere lo stacked widget
QStackedWidget* MainWindow::getStackedWidget() const
{
    return stackedWidget;
}
