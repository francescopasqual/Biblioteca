#include "itemdetailscreen.h"

// In itemdetailscreen.cpp

void ItemDetailScreen::clearFormatsLayout()
{
    QLayoutItem* itemToTake;
    // Raccogli i widget da cancellare (quelli che non sono formatsTitle)
    std::vector<QWidget*> widgetsToDelete;

    // Rimuovi TUTTI i layout item dal layout formatsLayout.
    // takeAt(0) rimuove sempre il primo elemento.
    // Iteriamo finché il layout non è vuoto prendendo l'elemento in posizione 0.
    while((itemToTake = formatsLayout->takeAt(0)) != nullptr) {
        // Se l'elemento del layout contiene un widget...
        if(itemToTake->widget()) {
            // ... e se quel widget *non* è formatsTitle (lo identifichiamo per objectName)
            if(itemToTake->widget()->objectName() != "FormatsTitleLabel") {
                // È un widget dinamico, aggiungilo alla lista di quelli da cancellare
                widgetsToDelete.push_back(itemToTake->widget());
            }
            // Il QLayoutItem che conteneva il widget (statico o dinamico) deve sempre essere cancellato.
        }
        // Cancella il QLayoutItem stesso (che sia un widget o uno stretch)
        delete itemToTake;
    }

    // Ora dealloca tutti i widget dinamici che abbiamo raccolto
    for(QWidget* w : widgetsToDelete) {
        delete w;
    }

    // A questo punto, formatsLayout è completamente vuoto.
    // formatsTitle (la label statica) non è stato cancellato, ma è stato rimosso dal layout.
    // Sarà riaggiunto in displayDetails()
}


ItemDetailScreen::ItemDetailScreen(QWidget *parent)
    : QWidget{parent}
{
    currentItem = nullptr; // Inizializza il puntatore a nullptr

    //layout principale
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    itemWidget = new QWidget(this);
    itemLayout = new QVBoxLayout(itemWidget);

    itemLayout->setAlignment(Qt::AlignTop); // Allinea il layout in alto

    //widget per i dettagli
    detailsWidget = new QGroupBox("Dettagli", itemWidget);
    detailsLayout = new QFormLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop); // Allinea il layout in alto

    // Label Titolo principale
    titleLabel = new QLabel("", itemWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(titleFont.pointSize() + 6); // Aumenta la dimensione
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);


    // Label statiche (create nel costruttore) per valori dinamici (popolati con metodo displayDetails())
    creatorValueLabel = new QLabel("", detailsWidget);
    genreValueLabel = new QLabel("", detailsWidget);
    yearValueLabel = new QLabel("", detailsWidget);
    copiesValueLabel = new QLabel("", detailsWidget);
    loansValueLabel = new QLabel("", detailsWidget);
    availabilityValueLabel = new QLabel("", detailsWidget);

    // Aggiungi le coppie etichetta-valore al detailsLayout (QFormLayout)
    detailsLayout->addRow("Creatore:", creatorValueLabel);
    detailsLayout->addRow("Genere:", genreValueLabel);
    detailsLayout->addRow("Anno:", yearValueLabel);
    detailsLayout->addRow("Copie totali:", copiesValueLabel);
    detailsLayout->addRow("Prestiti attivi:", loansValueLabel);
    detailsLayout->addRow("Disponibilità:", availabilityValueLabel);

    //widget per i formati
    formatsWidget = new QGroupBox("Formati", itemWidget);
    formatsLayout = new QVBoxLayout(formatsWidget);
    formatsLayout->setAlignment(Qt::AlignTop); // Allinea il layout in alto

    formatsTitle = new QLabel("Formati Disponibili:", formatsWidget);
    formatsTitle->setObjectName("FormatsTitleLabel"); // Imposta un nome per identificare il widget //debugging
    //formatsTitle verrà aggiunto al layout da displayDetails
    //altrimenti quando chiamo clearFormatsLayout crasha (perché non è più nel layout)
    //infatti clearFormatsLayout() rimuove tutti i widget dal layout e displayDetails() tenterebbe di usarlo
    //label dinamiche create in displayDetails

    itemLayout->addWidget(detailsWidget);
    itemLayout->addWidget(formatsWidget);

    //pulsanti finali
    exitButton = new QPushButton("Esci", this);
    loanButton = new QPushButton("Richiedi in prestito", this);
    keepButton = new QPushButton("Tieni", this);
    buttonsWidget = new QGroupBox("Azioni", this);
    buttonsLayout = new QHBoxLayout(buttonsWidget);
    buttonsLayout->addWidget(exitButton);
    buttonsLayout->addWidget(loanButton);
    buttonsLayout->addWidget(keepButton);
    buttonsLayout->setAlignment(Qt::AlignTop); // Allinea il layout in alto

    //aggiungere al layout principale
    mainLayout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(itemWidget, 1); // Aggiungi il widget item (che contiene dettagli e formati)
    mainLayout->addWidget(buttonsWidget, 0, Qt::AlignBottom);
    mainLayout->addStretch(1);

    //connect
    connect(exitButton, &QPushButton::clicked, this, &ItemDetailScreen::onExitButtonClicked);
    connect(loanButton, &QPushButton::clicked, this, &ItemDetailScreen::onLoanButtonClicked);
    connect(keepButton, &QPushButton::clicked, this, &ItemDetailScreen::onKeepButtonClicked);
}

void ItemDetailScreen::displayDetails(Item *item)
{
    currentItem = item;

    //se puntatore nullo
    if(!item){

        // Pulisci le label dei dettagli principali
        titleLabel->setText("Nessun articolo selezionato");
        creatorValueLabel->setText("");
        genreValueLabel->setText("");
        yearValueLabel->setText("");
        copiesValueLabel->setText("");
        loansValueLabel->setText("");
        availabilityValueLabel->setText("");
        availabilityValueLabel->setStyleSheet("");

        clearFormatsLayout();

        //RIAGGIUNGERE GLI ELEMENTI STATICI RIMOSSI DA clearFormatsLayout()
        // Aggiungi la label statica del titolo della sezione formati (rimossa da clearFormatsLayout)
        formatsLayout->addWidget(formatsTitle);

        // Aggiungi un messaggio nell'area formati per indicare che nessun item è selezionato
        QLabel* noItemMessageLabel = new QLabel("Seleziona un articolo dalla lista o dal catalogo per visualizzarne i dettagli.", formatsWidget); // Parent è formatsWidget
        noItemMessageLabel->setWordWrap(true); // Abilita wrap testo
        noItemMessageLabel->setAlignment(Qt::AlignCenter); // Centra il messaggio
        formatsLayout->addWidget(noItemMessageLabel);

        // Aggiungi uno stretch per spingere il messaggio in alto nell'area formati
        formatsLayout->addStretch(1);

        // Disabilita i pulsanti di azione che richiedono un item valido
        loanButton->setEnabled(false);
        keepButton->setEnabled(false);

        qDebug() << "ItemDetailScreen::displayDetails: Item* ricevuto nullo. Schermata resettata.";

        return;

    }
    //altrimenti ci è stato passato un vero puntatore a un item

    //POPOLARE LA SEZIONE DELLE INFO PRINCIPALI
    titleLabel->setText(QString::fromStdString(item->getTitolo()));
    // Aggiorno label dei valori
    creatorValueLabel->setText(QString::fromStdString(item->getCreatore()));
    genreValueLabel->setText(QString::fromStdString(item->getGenere()));
    yearValueLabel->setText(QString::fromStdString(item->getAnno()));
    copiesValueLabel->setText(QString::number(item->getCopie()));
    loansValueLabel->setText(QString::number(item->getPrestiti()));

    //Logica di disponibilità al prestito
    if (item->isAvailable()) {
        availabilityValueLabel->setText("Disponibile (" + QString::number(item->getCopie() - item->getPrestiti()) + " copie)");
        availabilityValueLabel->setStyleSheet("color: green; font-weight: bold;");
    } else {
        availabilityValueLabel->setText("Non disponibile");
        availabilityValueLabel->setStyleSheet("color: red; font-weight: bold;");
    }

    //POPOLO LA SEZIONE DEI FORMATI
    clearFormatsLayout(); //pulizia
    formatsLayout->addWidget(formatsTitle); //aggiungo la label statica

    std::vector<Formato*> formati = item->getFormati(); //formati di item

    if (!formati.empty()) {
        for (Formato* formato : formati) {

            std::string descrizioneFormato = formato->descrizione();

            // Crea una nuova label dinamica per questa descrizione del formato
            QLabel* formatDescLabel = new QLabel(QString::fromStdString(descrizioneFormato), formatsWidget);
            formatDescLabel->setWordWrap(true); //wrap del testo se lungo

            // Aggiungo la label al layout dei formati (lasciato incompleto nel costruttore)
            formatsLayout->addWidget(formatDescLabel);
        }

        formatsLayout->addStretch(1);

    } else {
        // Messaggio se non ci sono formati
        //Unica label che fornisce l'informazione all'utente
        QLabel* noFormatsLabel = new QLabel("Nessun formato specificato per questo articolo.", formatsWidget);
        formatsLayout->addWidget(noFormatsLabel);
        formatsLayout->addStretch(1);
    }

    //BOTTONI
    //aggiorno lo stato (se cliccabile o meno) a seconda delle proprietà dell'item
    loanButton->setEnabled(item->isAvailable());
    keepButton->setEnabled(item->getPrestiti() > 0);
}


void ItemDetailScreen::onExitButtonClicked()
{
    qDebug() << "ItemDetailScreen::onExitButtonClicked() called";
    emit exitRequest();
}

void ItemDetailScreen::onLoanButtonClicked()
{
    qDebug() << "ItemDetailScreen::onLoanButtonClicked() called";
    // Emette il segnale passando il puntatore all'item corrente visualizzato
    if (currentItem) {
        emit loanRequest(currentItem);
    } else {
        qWarning() << "ItemDetailScreen::onLoanButtonClicked: currentItem is null. Segnale non emesso.";
    }
}

void ItemDetailScreen::onKeepButtonClicked()
{
    qDebug() << "ItemDetailScreen::onReturnButtonClicked() called";
    // Emette il segnale passando il puntatore all'item corrente visualizzato
    if (currentItem) {
        emit keepRequest(currentItem);
    } else {
        qWarning() << "ItemDetailScreen::onReturnButtonClicked: currentItem is null. Segnale non emesso.";
    }
}


