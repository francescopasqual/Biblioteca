#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
{
    Model = new Biblioteca();
    loginView = new LoginWindow;
    catalogView = new CatalogWindow;
    authenticator = new Authenticator();

    /* 2. Stabilire le connessioni tra View e Controller.
        // Il Controller si connette ai segnali delle View a cui deve reagire.
        // Sintassi: connect(Sorgente, &ClasseSorgente::Segnale, Destinazione, &ClasseDestinazione::Slot);

        // Ci connettiamo dal segnale loginRequested della loginView allo slot handleLoginRequest in questo Controller.
        // Quando l'utente clicca "Accedi" nella LoginWindow (e LoginWindow emette il segnale),
        // viene chiamato il metodo handleLoginRequest nel AppController.
    */

    connect(loginView, &LoginWindow::loginRequested, this, &AppController::handleLoginRequest);


    // 4. Assicurarsi che le View non iniziali siano nascoste.
    // La CatalogView non deve essere visibile all'avvio.
    catalogView->hide();
    // loginView->hide(); // Non nascondiamo la loginView qui, perché la mostriamo subito dopo in start().
}

AppController::~AppController()
{
    delete Model;
    delete loginView;
    delete catalogView;
    delete authenticator;
}

void AppController::start()
{
    loginView->show();
}

void AppController::handleLoginRequest(const QString &username, const QString &password)
{
    bool loginSuccess = authenticator->verificaCredenziali(username, password);

    if(loginSuccess){
        loginView->hide();
        catalogView->show();

    }else {
        // Mostra un messaggio di errore nella LoginWindow
        loginView->showErrorMessage("Credenziali non valide. Riprova.");
    }


}

void AppController::handleGlobalSearch(const QString &query)
{
    //logica per chiamare il modello e cambiare view
}

void AppController::handleCategorySelected(const QString &categoryName)
{

}
