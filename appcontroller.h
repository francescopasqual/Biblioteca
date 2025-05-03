#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "biblioteca.h"
#include "loginscreen.h"
#include "catalogscreen.h"
#include "authenticator.h"
#include <QDebug>
#include "mainwindow.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QString>

class AppController : public QObject
{
    Q_OBJECT

private:

    MainWindow* mainWindow;
    QStackedWidget* stackedWidget;
    Biblioteca* bibliotecaModel;
    Authenticator* authenticator;
    LoginScreen* loginScreen;;
    CatalogScreen* catalogScreen;



public:

    AppController(QObject *parent = nullptr);

    ~AppController();

    void start();

private slots:

    // Slot to handle login requests from the view
    /* Riceve username e password dal segnale loginRequested della LoginWindow.
       Questo metodo viene chiamato quando l'utente clicca "Accedi" nella LoginWindow.
       Qui implementiamo la logica per verificare le credenziali immesse
    */
    void handleLoginRequest(const QString& username, const QString& password);

    void handleGlobalSearch(const QString& query);

    void handleCategorySelected(const QString& categoryName);



signals:
};

#endif // APPCONTROLLER_H
