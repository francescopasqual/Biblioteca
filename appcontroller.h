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
#include <itemlistscreen.h>
#include <QWidget>
#include <QTableWidgetItem>
#include <QVariant>
#include "itemdetailscreen.h"
#include <set>
#include <algorithm>
#include <QMessageBox>
#include <QVector>
#include "libro.h"
#include "film.h"
#include "vinile.h"
#include "disco.h"
#include "mp4.h"
#include "epub.h"
#include "cartaceo.h"

class AppController : public QObject
{
    Q_OBJECT

private:

    //mainwindow
    MainWindow* mainWindow;
    QStackedWidget* stackedWidget;

    //modello
    Biblioteca* bibliotecaModel;
    Authenticator* authenticator;

    //view
    LoginScreen* loginScreen;;
    CatalogScreen* catalogScreen;
    ItemListScreen* listScreen;
    ItemDetailScreen* detailScreen;

    //Pila di navigazione per tenere traccia del flusso delle schermate
    //va aggiornata ogni qualvolta cambio schermata
    std::vector<QWidget*> navigationStack;

    //funzione helper per la navigazione all'indietro
    void navigateBack();

    //funzione helper per gestione dei risultati di una ricerca e passaggio di schermate
    void operateOnSearchResults(const std::vector<Item*>& results, const QString& query);


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

    //Finestra login
    void handleLoginRequest(const QString& username, const QString& password);

    //Finestra catalog
    void handleGlobalSearch(const QString& query);
    void handleCategorySelected(const QString& categoryName);

    //Finestra item list
    void handleItemListClicked(Item* selectedItem);
    void handleReturnToCatalogRequest(); //dalla item list screen

    //Finestra dettagli
    void handleLoanRequest(Item* item);
    void handleKeepRequest(Item* item);
    void handleExitDetailsRequest(); //dalla finestra di dettagli



signals:


};

#endif // APPCONTROLLER_H
