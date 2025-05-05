#include "appcontroller.h"

void AppController::navigateBack()
{
    //se è effettivamente possibile tornare indietro nel flusso di navigazione
    //quindi se la pila ha più di un elemento
    if(navigationStack.size()>1){
        //rimuovo l'ultimo elemento (finestra attuale)
        navigationStack.pop_back();
        //imposto la nuova finestra (che ora è l'ultimo elemento del vettore)
        stackedWidget->setCurrentWidget(navigationStack.back());
    } else {
    // Questo caso si verifica se siamo nella schermata iniziale (pila ha 1 elemento)
    // o se la pila è vuota (problema logico grave).
    qWarning() << "AppController: Pila di navigazione insufficiente. Impossibile tornare indietro.";
    // Puoi decidere di rimanere nella schermata attuale, mostrare un messaggio, ecc.
    // Per ora, non facciamo nulla (rimane nella schermata attuale).
}
}

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
    listScreen = new ItemListScreen(stackedWidget);
    detailScreen = new ItemDetailScreen(stackedWidget);

    //Aggiungere le schermate allo stackedwidget
    stackedWidget->addWidget(loginScreen); //indice 0
    stackedWidget->addWidget(catalogScreen); //indice 1
    stackedWidget->addWidget(listScreen); //indice 2
    stackedWidget->addWidget(detailScreen); //indice 3

    //IMPOSTARE LA SCHERMATA QWIDGET INIZIALE NELLO STACKEDWIDGET
    qDebug() << "AppController: Impostando la schermata iniziale: LoginScreen.";
    stackedWidget->setCurrentWidget(loginScreen);
    //settare la pila
    navigationStack.push_back(loginScreen); //aggiunta la schermata iniziale alla pila

    //Connessioni LoginScreen
    connect(loginScreen, &LoginScreen::loginRequested, this, &AppController::handleLoginRequest);

    // Connessioni CatalogScreen -> Controller (Richieste di Ricerca e Selezione Categoria)
    connect(catalogScreen, &CatalogScreen::globalSearchRequested, this, &AppController::handleGlobalSearch);
    connect(catalogScreen, &CatalogScreen::categorySelected, this, &AppController::handleCategorySelected);

    //Connessioni ItemListScreen -> Controller (selezione di un item dal listone e click del pulsante indietro)
    connect(listScreen, &ItemListScreen::backRequested, this, &AppController::handleReturnToCatalogRequest);
    connect(listScreen, &ItemListScreen::itemSelected, this, &AppController::handleItemListClicked);

    //Connessioni ItemDetailScreen -> Controller (richiesta di prestito e ritorno)
    connect(detailScreen, &ItemDetailScreen::exitRequest, this, &AppController::handleExitDetailsRequest);
    connect(detailScreen, &ItemDetailScreen::loanRequest, this, &AppController::handleLoanRequest);
    connect(detailScreen, &ItemDetailScreen::keepRequest, this, &AppController::handleKeepRequest);
}



AppController::~AppController() {delete mainWindow;}




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
        navigationStack.push_back(catalogScreen);
        stackedWidget->setCurrentWidget(catalogScreen);

    }else {
        // Se le credenziali non sono valide, mostra un messaggio di errore
        qDebug() << "AppController: Credenziali non valide. Mostrando messaggio di errore.";
        loginScreen->showErrorMessage("Credenziali non valide. Riprova.");
    }
}



// --- Gestione dei risultati della ricerca per categoria ---
// La logica è identica a quella della ricerca globale:
// 0 risultati -> messaggio di errore su CatalogScreen
// 1 risultato -> mostra ItemDetailScreen con l'item
// >1 risultati -> mostra ItemListScreen con i risultati

void AppController::handleGlobalSearch(const QString &query)
{
    qDebug() << "AppController: Richiesta ricerca globale con query:" << query;
    std::string stdQuery = query.toStdString();

    //RICERCHE SINGOLE
    //ricerca per titolo
    std::vector<Item*> resultsByTitle = bibliotecaModel->searchByTitle(stdQuery);

    // Ricerca per creatore (autore, regista, performer)
    std::vector<Item*> resultsByCreator;
    std::vector<Item*> authorResults = bibliotecaModel->searchByAuthor(stdQuery);
    std::vector<Item*> registaResults = bibliotecaModel->searchByRegista(stdQuery);
    std::vector<Item*> performerResults = bibliotecaModel->searchByPerformer(stdQuery);

    // Elimino i duplicati dai creatori
    std::set<Item*> uniqueCreatorResults;
    for(Item* item : authorResults) uniqueCreatorResults.insert(item);
    for(Item* item : registaResults) uniqueCreatorResults.insert(item);
    for(Item* item : performerResults) uniqueCreatorResults.insert(item);
    resultsByCreator.assign(uniqueCreatorResults.begin(), uniqueCreatorResults.end()); // Copia nel vettore

    / Mostra un messaggio di errore all'utente
        QMessageBox::warning(stackedWidget->currentWidget(),
                                                                       "Restituzione Non Riuscita",
                                                                       "Impossibile registrare la restituzione per '" + QString::fromStdString(item->getTitolo()) +
                                                                           "'. Possibile errore server. Riprovare più tardi.");
    // Ricerca per Anno (solo se la query è un numero valido)
    std::vector<Item*> resultsByYear;
    bool isNumber = false;
    int year = query.toInt(&isNumber); // Tenta di convertire la query in int
    if (isNumber) {
        qDebug() << "AppController: Query rilevata come anno:" << year;
        resultsByYear = bibliotecaModel->searchByYear(year);
    }

    //Combina i risultati delle ricerche
    std::set<Item*> finalUniqueResults; // Usa un set per garantire unicità

    // Aggiungi i risultati di ogni ricerca al set
    for(Item* item : resultsByTitle) finalUniqueResults.insert(item);
    for(Item* item : resultsByCreator) finalUniqueResults.insert(item);
    for(Item* item : resultsByYear) finalUniqueResults.insert(item);

    // Converti il set di puntatori unici in un vettore per i risultati finali
    std::vector<Item*> finalResults(finalUniqueResults.begin(), finalUniqueResults.end());

    //GESTIONE DEI RISULTATI DELLA RICERCA

    // Se la ricerca non ha prodotto risultati
    if(finalResults.empty()){
        qDebug() << "AppController: Nessun risultato trovato per la ricerca globale.";
        // Mostra un messaggio di errore sulla schermata di catalogo (da cui è partita la ricerca)
        catalogScreen->showErrorMessage("Nessun risultato trovato per '" + query + "'.");

    }
    // Altrimenti, se contiene un solo item
    else if(finalResults.size()==1){
        qDebug() << "AppController: Un risultato (" << QString::fromStdString(finalResults[0]->getTitolo()) << ") trovato per la ricerca globale. Mostrando dettagli.";
        // Ottieni il puntatore all'unico item trovato
        Item* foundItem = finalResults[0];
        navigationStack.push_back(stackedWidget->currentWidget()); //aggiorno la pila per memorizzare la finestra corrente
        detailScreen->displayDetails(foundItem); // Passa l'item alla schermata di dettaglio
        stackedWidget->setCurrentWidget(detailScreen); // mostro (passo) alla finestra di dettaglio

    }
    // Altrimenti (se contiene più item)
    else{
        qDebug() << "AppController: Più risultati (" << finalResults.size() << ") trovati per la ricerca globale. Mostrando lista.";
        // Chiama il metodo della ItemListScreen per popolare la tabella con i risultati
        navigationStack.push_back(stackedWidget->currentWidget()); //memorizzo nella pila la finestra corrente
        listScreen->toInsertItems(finalResults, "Risultati per '" + query + "'");
        stackedWidget->setCurrentWidget(listScreen); // Mostra la schermata della lista
    }
}




void AppController::handleCategorySelected(const QString &categoryName)
{
    qDebug() << "AppController: Richiesta selezione categoria (mostra tutti gli item del tipo):" << categoryName;

    std::vector<Item*> allItems = bibliotecaModel->getCatalogo(); // Ottieni tutto il catalogo
    std::vector<Item*> filteredItems; // Vettore per i risultati filtrati

    //FILTRO DEGLI ITEM NEL CATALOGO

    //Libri
    if(categoryName == "Libri"){
        qDebug() << "AppController: Filtrando per tipo: Libro.";
        for(Item* item : allItems) {
            if(dynamic_cast<Libro*>(item) != nullptr) { // Se l'item è un Libro (o una sottoclasse di Libro)
                filteredItems.push_back(item); // Aggiungilo ai risultati filtrati
            }
        }

    //Film
    }else if(categoryName == "Film"){
        qDebug() << "AppController: Filtrando per tipo: Film.";
        for(Item* item : allItems) {
            if(dynamic_cast<Film*>(item) != nullptr) { // Se l'item è un Film (o una sottoclasse di Film)
                filteredItems.push_back(item);
            }
        }

    //Vinili
    }else if (categoryName == "Vinili"){
        qDebug() << "AppController: Filtrando per tipo: Vinile.";
        for(Item* item : allItems) {
            if(dynamic_cast<Vinile*>(item) != nullptr) { // Se l'item è un Vinile (o una sottoclasse di Vinile)
                filteredItems.push_back(item);
            }
        }

    } else {
        qWarning() << "AppController: Categoria non gestita:" << categoryName;
        // Mostra un messaggio di errore sul catalogScreen
        catalogScreen->showErrorMessage("Categoria non riconosciuta: '" + categoryName + "'.");
        return; // Esci dalla funzione se la categoria non è valida
    }


    //Gestione dei risultati filtrati
    if(filteredItems.empty()){
        qDebug() << "AppController: Nessun item trovato nella categoria:" << categoryName;
        catalogScreen->showErrorMessage("Nessun articolo trovato nella categoria '" + categoryName + "'.");

    }
    // Se c'è esattamente un item del tipo filtrato (poco probabile se ci sono molti item, ma possibile)
    else if(filteredItems.size()==1){
        qDebug() << "AppController: Un solo item trovato nella categoria:" << categoryName << ". Mostrando dettagli.";
        Item* foundItem = filteredItems[0];
        navigationStack.push_back(stackedWidget->currentWidget()); //aggiorno la pila per memorizzare la finestra corrente
        detailScreen->displayDetails(foundItem);
        stackedWidget->setCurrentWidget(detailScreen); // Mostra la schermata di dettaglio

    }
    // Altrimenti (più di un item del tipo filtrato)
    else{
        qDebug() << "AppController: Trovati (" << filteredItems.size() << ") item nella categoria:" << categoryName << ". Mostrando lista.";
        navigationStack.push_back(stackedWidget->currentWidget()); //memorizzo nella pila la finestra corrente
        listScreen->toInsertItems(filteredItems, "Articoli nella categoria '" + categoryName + "'"); // Passa i risultati filtrati e il titolo
        stackedWidget->setCurrentWidget(listScreen); // Mostra la schermata della lista
    }
}



void AppController::handleItemListClicked(Item* selectedItem) // Riceve il puntatore Item* dal segnale itemSelected
{
    if (!selectedItem) { // Controllo di sicurezza, anche se la ItemListScreen dovrebbe emettere solo puntatori validi
        qWarning() << "AppController::handleItemListClicked: Ricevuto puntatore Item* nullo.";
        return;
    }

    qDebug() << "AppController: Item selezionato dalla lista:" << QString::fromStdString(selectedItem->getTitolo()) << ". Mostrando dettagli.";

    //Aggiorno la pila memorizzando la schermata corrente
    navigationStack.push_back(stackedWidget->currentWidget());
    detailScreen->displayDetails(selectedItem);
    stackedWidget->setCurrentWidget(detailScreen); //la mostro
}


// Slot chiamato quando si clicca "Indietro" nella ItemListScreen
// Questo riporta al catalogo
// N.B: però la itemlistscreen è raggiungibile anche dopo aver cliccato su una categori, ci sta quindi
// perchè l'elenco delle categorie si trova nella catalogScreen
void AppController::handleReturnToCatalogRequest()
{
    qDebug() << "App Controller: Richiesta di tornare indietro dalla lista.";
    // Chiama la funzione helper per gestire la navigazione indietro generale
    navigateBack();
}



void AppController::handleLoanRequest(Item *item)
{
    // Controllo di sicurezza aggiuntivo, anche se il segnale dalla View dovrebbe essere valido
    if (!item) {
        qWarning() << "AppController::handleLoanRequest: Ricevuto puntatore Item* nullo.";
        QMessageBox::warning(stackedWidget->currentWidget(),
                             "Errore di Prestito",
                             "Impossibile procedere con il prestito: articolo non valido.");
        return;
    }

    qDebug() << "AppController: Richiesta di prestito per l'item:" << QString::fromStdString(item->getTitolo());

    // Chiama il metodo del modello per tentare il prestito
    if(bibliotecaModel->prestaItem(item)){ // se restituisce true, il prestito è riuscito
        qDebug() << "AppController: Prestito riuscito per:" << QString::fromStdString(item->getTitolo());

        // Mostra un messaggio di successo all'utente
        QMessageBox::information(stackedWidget->currentWidget(),
                                 "Prestito Riuscito",
                                 "Il prestito per '" + QString::fromStdString(item->getTitolo()) + "' è stato registrato con successo!");

        // Il metodo prestaItem ha modificato lo stato interno dell'item => aggiorno la sua finestra di dettaglio
        //Saranno cambiati i campi numero_prestiti e disponibilità.
        detailScreen->displayDetails(item);

    } else { // se restituisce false, il prestito non è riuscito (es. item non disponibile)
        qDebug() << "AppController: Prestito non riuscito per:" << QString::fromStdString(item->getTitolo());

        // Mostra un messaggio di errore all'utente
        QMessageBox::warning(stackedWidget->currentWidget(),
                             "Prestito Non Riuscito",
                             "Impossibile registrare il prestito per '" + QString::fromStdString(item->getTitolo()) +
                             "'. L'articolo potrebbe non essere disponibile.");
    }
}


void AppController::handleKeepRequest(Item *item)
{
    // Controllo di sicurezza aggiuntivo, anche se il segnale dalla View dovrebbe essere valido
    if (!item) {
        qWarning() << "AppController::handleKeepRequest: Ricevuto puntatore Item* nullo.";
        QMessageBox::warning(stackedWidget->currentWidget(),
                             "Errore di Restituzione",
                             "Impossibile procedere con la restituzione: articolo non valido.");
        return;
    }

    qDebug() << "AppController: Richiesta di restituzione per l'item:" << QString::fromStdString(item->getTitolo());

    if(bibliotecaModel->restituisciItem(item)){ //se true posso restituire
        qDebug() << "AppController: Restituzione riuscita per:" << QString::fromStdString(item->getTitolo());

        // Mostra un messaggio di successo all'utente
        QMessageBox::information(stackedWidget->currentWidget(),
                                 "Restituzione Riuscita",
                                 "La Restituzione per '" + QString::fromStdString(item->getTitolo()) + "' è stata registrata con successo!");

        // Il metodo restituisciItem ha modificato lo stato interno dell'item => aggiorno la sua finestra di dettaglio
        //Saranno cambiati i campi numero_prestiti e disponibilità.
        detailScreen->displayDetails(item);

    } else { // se restituisce false, la restituzione non è riuscita
        qDebug() << "AppController: Restituzione non riuscita per:" << QString::fromStdString(item->getTitolo());

        QMessageBox::warning(stackedWidget->currentWidget(),
                             "Restituzione Non Riuscita",
                             "Impossibile registrare la restituzione per '" + QString::fromStdString(item->getTitolo()) +
                             "'. Possibile errore: l'articolo non risulta in prestito."); // Messaggio più specifico
    }
}




// Slot chiamato quando si clicca "Esci" nella ItemDetailScreen
void AppController::handleExitDetailsRequest()
{
    qDebug() << "AppController: Richiesta di uscire dalla schermata dettagli.";
    // Chiama la funzione helper per gestire la navigazione indietro generale
    navigateBack();
}






