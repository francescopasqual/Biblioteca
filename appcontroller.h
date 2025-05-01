#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "biblioteca.h"
#include "loginwindow.h"
#include "catalogwindow.h"
#include "authenticator.h"
#include <QDebug>

class AppController : public QObject
{
    Q_OBJECT

private:
    Biblioteca* Model;
    LoginWindow* loginView;
    CatalogWindow* catalogView;
    Authenticator* authenticator;


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



signals:
};

#endif // APPCONTROLLER_H
