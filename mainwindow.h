#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtmetamacros.h"
#include <QMainWindow>
#include <QStackedWidget> // Necessario per lo stacked widget
#include <QWidget> // Necessario per QWidget

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QStackedWidget* stackedWidget; // Il widget che impila le nostre schermate

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); // Distruttore per pulizia se necessaria

    // Metodo pubblico per ottenere il puntatore allo stacked widget.
    // Il Controller ne avrà bisogno per aggiungere e cambiare le schermate.
    QStackedWidget* getStackedWidget() const;

};
#endif // MAINWINDOW_H
