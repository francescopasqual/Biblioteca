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
        qWarning() << "AppController: Pila di navigazione insufficiente. Impossibile tornare indietro.";
        // Per ora non lo gestisco
    }
}


// --- Gestione dei risultati della ricerca per categoria ---
// 0 risultati -> messaggio di errore su CatalogScreen
// 1 risultato -> mostra ItemDetailScreen con l'item
// >1 risultati -> mostra ItemListScreen con i risultati
void AppController::operateOnSearchResults(const std::vector<Item *> &results, const QString &query)
{
    qDebug() << "AppController: Operazione sui risultati della ricerca. Risultati trovati:" << results.size();

    // Se non ci sono risultati, mostra un messaggio di errore
    if (results.empty()) {
        qDebug() << "AppController: Nessun risultato trovato per la query:" << query;
        catalogScreen->showErrorMessage("Nessun risultato trovato per la query: '" + query + "'.");
        return;
    }

    // Se c'è un solo risultato, mostra i dettagli dell'item
    if (results.size() == 1) {
        qDebug() << "AppController: Un solo risultato trovato. Mostrando dettagli.";
        handleItemListClicked(results[0]); // Passa il puntatore all'item alla funzione di gestione dei dettagli
        return;
    }

    // Se ci sono più risultati, mostra la lista degli item
    qDebug() << "AppController: Più di un risultato trovato. Mostrando lista.";
    listScreen->toInsertItems(results, query); // Passa il vettore di risultati alla ItemListScreen
    stackedWidget->setCurrentWidget(listScreen); // Mostra la schermata della lista
}







AppController::AppController(QObject *parent)
    : QObject{parent}
{
    mainWindow = new MainWindow();
    stackedWidget = new QStackedWidget(mainWindow);
    mainWindow->setCentralWidget(stackedWidget);

    //Istanze del modello
    bibliotecaModel = new Biblioteca(this);

    // --- Popolare la Biblioteca con dati di test ---
    qDebug() << "AppController: Popolando la biblioteca con dati di test...";

    // Esempio: Aggiungi un Libro
    Libro* libro1 = new Libro("Il Signore degli Anelli", "J.R.R. Tolkien", "Fantasy", 1954, 5, 2, 500, this); // Parent è AppController
    libro1->addFormato(new Cartaceo("978-8845292613", libro1)); // Parent è il libro
    libro1->addFormato(new Epub(15, libro1)); // Parent è il libro
    bibliotecaModel->addItem(libro1);
    // Esempio: Aggiungi un altro Libro
    Libro* libro2 = new Libro("1984", "George Orwell", "Dystopian", 1949, 2, 1, 300, this); // Parent è AppController
    libro2->addFormato(new Cartaceo("978-0451524935", libro2)); // Parent è il libro
    libro2->addFormato(new Epub(10, libro2)); // Parent è il libro
    bibliotecaModel->addItem(libro2);

    // Esempio: Aggiungi un Film
    Film* film1 = new Film("Inception", "Christopher Nolan", "Sci-Fi", 2010, 3, 1, 120, "Stocazzo", this); // Parent AppController
    film1->addFormato(new Disco(148, film1)); // Parent il film
    film1->addFormato(new Mp4(2000, 148, film1)); // Parent il film
    bibliotecaModel->addItem(film1);

    // Esempio: Aggiungi un Vinile
    Vinile* vinile1 = new Vinile("Kind of Blue", "Miles Davis", "Jazz", 1959, 2, 0, 5, 55, this); // Parent AppController
    vinile1->addFormato(new Disco(45, vinile1)); // Un vinile può essere considerato un tipo di disco fisico
    bibliotecaModel->addItem(vinile1);

    // Aggiungi altri item di test con diversi formati, disponibilità, ecc.
    // Assicurati che i costruttori delle tue classi Item e Formato accettino un QObject* parent.

    qDebug() << "AppController: Popolazione dati di test completata. Items nel catalogo:" << bibliotecaModel->getCatalogo().size();
    // --- Fine popolamento dati di test ---

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
    // Chiama la funzione helper per gestire i risultati della ricerca
    operateOnSearchResults(finalResults, "Risultati per '" + query + "'"); // <<< Passa il titolo della ricerca globale
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
    // Chiama la funzione helper per gestire i risultati della ricerca
    operateOnSearchResults(filteredItems, "Risultati per categoria: '" + categoryName + "'"); // <<< Passa il titolo della ricerca per categoria
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

