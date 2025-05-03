#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
{
    mainWindow = new MainWindow();
    stackedWidget = new QStackedWidget(mainWindow);
    mainWindow->setCentralWidget(stackedWidget);

    //Istanze del modello
    bibliotecaModel = new Biblioteca(this);
    authenticator = new Authenticator(this);

    //Istanze delle schermate
    loginScreen = new LoginScreen(stackedWidget);
    catalogScreen = new CatalogScreen(stackedWidget);

    //Aggiungere le schermate allo stackedwidget
    stackedWidget->addWidget(loginScreen); //indice 0
    stackedWidget->addWidget(catalogScreen); //indice 1


    /* 2. Stabilire le connessioni tra View e Controller.
        // Il Controller si connette ai segnali delle View a cui deve reagire.
        // Sintassi: connect(Sorgente, &ClasseSorgente::Segnale, Destinazione, &ClasseDestinazione::Slot);

        // Ci connettiamo dal segnale loginRequested della loginView allo slot handleLoginRequest in questo Controller.
        // Quando l'utente clicca "Accedi" nella LoginWindow (e LoginWindow emette il segnale),
        // viene chiamato il metodo handleLoginRequest nel AppController.
    */

    //Connessioni LoginScreen
    connect(loginScreen, &LoginScreen::loginRequested, this, &AppController::handleLoginRequest);

    // Connessioni CatalogScreen -> Controller (Richieste di Ricerca e Selezione Categoria)
        connect(catalogScreen, &CatalogScreen::globalSearchRequested,
                this, &AppController::handleGlobalSearch);
    connect(catalogScreen, &CatalogScreen::categorySelected,
            this, &AppController::handleCategorySelected);


    //IMPOSTARE LA SCHERMATA QWIDGET INIZIALE NELLO STACKEDWIDGET
    qDebug() << "AppController: Impostando la schermata iniziale: LoginScreen.";
    stackedWidget->setCurrentWidget(loginScreen);
}

AppController::~AppController()
{
    delete mainWindow;
}

void AppController::start()
{
    // Mostra la Main Window di partenza, principale.
    qDebug() << "AppController: Mostrando la MainWindow.";
    mainWindow->show();
}

void AppController::handleLoginRequest(const QString &username, const QString &password)
{
    bool loginSuccess = authenticator->verificaCredenziali(username, password);

    if(loginSuccess){
        // Se le credenziali sono valide, mostra la schermata CatalogScreen
        qDebug() << "AppController: Credenziali valide. Passando alla CatalogScreen.";
        stackedWidget->setCurrentWidget(catalogScreen);

    }else {
        // Se le credenziali non sono valide, mostra un messaggio di errore
        qDebug() << "AppController: Credenziali non valide. Mostrando messaggio di errore.";
        loginScreen->showErrorMessage("Credenziali non valide. Riprova.");
    }


}

void AppController::handleGlobalSearch(const QString &query)
{
    //logica per chiamare il modello e cambiare view
    std::string stdQuery = query.toStdString();

    std::vector<Item*> results = bibliotecaModel->searchByTitle(stdQuery);

    //se la ricerca non ha prodotto risultati
    if(results.empty()){
        qDebug() << "AppController: Nessun risultato trovato per la ricerca globale.";
        catalogScreen->showErrorMessage("Nessun risultato trovato.");

    /*Altrimenti:
     * - se contiene un solo item => mostriamo una finestra specifica per l'item dettagliato
     * - se contiene più item => mostriamo una finestra con la lista dei risultati
     * */
    }else if(results.size()==1){
        qDebug() << "AppController: Un risultato trovato per la ricerca globale.";
        //mostrare una finestra specifica per l'item dettagliato
    }else{
        qDebug() << "AppController: Più risultati trovati per la ricerca globale.";
        //mostrare una finestra con la lista dei risultati
    }
}



void AppController::handleCategorySelected(const QString &categoryName)
{
    std::string stdCategoryName = categoryName.toStdString();

    std::vector<Item*> results;

    //distinzione per le 3 categorie
    if(categoryName == "Libri"){
        results = bibliotecaModel->searchByGenre(stdCategoryName);
    }else if(categoryName == "Film"){
        results = bibliotecaModel->searchByGenere(stdCategoryName);
    }else {

    }
}
