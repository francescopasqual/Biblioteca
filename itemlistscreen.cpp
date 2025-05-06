#include "itemlistscreen.h"

ItemListScreen::ItemListScreen(QWidget *parent)
    : QWidget{parent}
{
    //layout principale della finestra
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    //widget e layout per la sezione superiore
    //(bottone per tornare indietro e landingLabel)
    upperSectionWidget = new QWidget(this);
    upperSectionLayout = new QHBoxLayout(upperSectionWidget);
    backButton = new QPushButton("Indietro", upperSectionWidget);
    upperSectionLayout->addWidget(backButton,0,Qt::AlignLeft);
    landingLabel = new QLabel(upperSectionWidget);
    landingLabel->setAlignment(Qt::AlignCenter); // Centra il testo nella label
    QFont titleFont = landingLabel->font();
    titleFont.setPointSize(titleFont.pointSize() + 4); // Aumenta la dimensione del font
    titleFont.setBold(true);
    landingLabel->setFont(titleFont);
    upperSectionLayout->addWidget(landingLabel);

    //aggiungo la upper al layout principale
    mainLayout->addWidget(upperSectionWidget,0,Qt::AlignTop);

    //TABELLA PER VISUALIZZARE GLI ITEM
    itemTable  = new QTableWidget(this);
    mainLayout->addWidget(itemTable); // Aggiungi la tabella al layout principale


    // --- Configurazione della QTableWidget ---
    // Decidi quante colonne e le loro intestazioni
    itemTable->setColumnCount(3); // Esempio: Titolo, Creatore, Anno
    QStringList headerLabels;
    headerLabels << "Titolo" << "Creatore" << "Anno";
    itemTable->setHorizontalHeaderLabels(headerLabels);

    // Configurazione intestazioni (header)
    itemTable->horizontalHeader()->setStretchLastSection(true); // L'ultima colonna si estende
    itemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // Le colonne si adattano al contenuto (inizialmente)

    // Comportamento di selezione
    itemTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disabilita modifica diretta
    itemTable->setSelectionBehavior(QAbstractItemView::SelectRows); // Seleziona l'intera riga
    itemTable->setSelectionMode(QAbstractItemView::SingleSelection); // Seleziona un solo item alla volta

    mainLayout->addStretch(1);


    //CONNESSIONI
    connect(backButton, &QPushButton::clicked, this, &ItemListScreen::onBackButtonClicked);
    connect(itemTable, &QTableWidget::itemClicked, this, &ItemListScreen::onItemClicked);
}

void ItemListScreen::onItemClicked(QTableWidgetItem* item)
{
    if (!item) return; // Controllo di sicurezza

    // Recupera il puntatore all'Item* originale che hai memorizzato usando setData(Qt::UserRole, ...)
    QVariant data = item->data(Qt::UserRole);
    Item* selectedItem = data.value<Item*>(); // Recupera il puntatore Item*

    if (selectedItem) {
        qDebug() << "Item cliccato:" << QString::fromStdString(selectedItem->getTitolo());
        // Emetti il segnale per notificare il Controller quale item è stato selezionato
        emit itemSelected(selectedItem); // AGGIUNGI Item* NELLA FIRMA DEL SEGNALE NELL'HEADER
    } else {
        qWarning() << "Errore: Puntatore Item* non trovato nell'item della tabella.";
    }
}

void ItemListScreen::onBackButtonClicked()
{
    // Emetti il segnale per notificare il Controller che l'utente ha cliccato "Indietro"
    emit backRequested();
}


//metodo per popolare la tabella
//il parametro items è un vettore di puntatori a Item restituito dalla ricerca
void ItemListScreen::toInsertItems(const std::vector<Item*>& items, const QString& searchTermOrCategory)
{
    // Imposta il testo del titolo per mostrare il parametro di ricerca/categoria
    landingLabel->setText("Risultati per: " + searchTermOrCategory);

    // Pulisce il contenuto attuale della tabella
    itemTable->clear(); // Pulisce la tabella
    itemTable->setRowCount(0); // Resetta il conteggio del numero di righe

    // Popola la tabella con gli item forniti
    itemTable->setRowCount(items.size()); // Imposta il numero di righe in base agli item

    for (size_t i = 0; i < items.size(); ++i) {
        Item* currentItem = items[i];

        // Crea gli item per ogni cella della riga corrente
        QTableWidgetItem* titleItem = new QTableWidgetItem(QString::fromStdString(currentItem->getTitolo()));
        QTableWidgetItem* creatorItem = new QTableWidgetItem(QString::fromStdString(currentItem->getCreatore()));
        QTableWidgetItem* yearItem = new QTableWidgetItem(QString::fromStdString(currentItem->getAnno())); // Converti int in QString

        // Memorizza il puntatore all'item originale in Qt::UserRole
        titleItem->setData(Qt::UserRole, QVariant::fromValue<Item*>(currentItem));
        creatorItem->setData(Qt::UserRole, QVariant::fromValue<Item*>(currentItem));
        yearItem->setData(Qt::UserRole, QVariant::fromValue<Item*>(currentItem));

        // Proprietà item: attivo e solo selezionabile
        titleItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        creatorItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        yearItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        // Inserire Iteme nella tabella: ciascuno nella cella corrispondente
        // "i" indica la riga della tabella; "0", "1", "2" indicano le celle (colonne)
        itemTable->setItem(i, 0, titleItem);
        itemTable->setItem(i, 1, creatorItem);
        itemTable->setItem(i, 2, yearItem);

        titleItem->setTextAlignment(Qt::AlignCenter);
        creatorItem->setTextAlignment(Qt::AlignCenter);
        yearItem->setTextAlignment(Qt::AlignCenter);
    }

    // Adatta le colonne al contenuto una volta che la tabella è stata popolata
    itemTable->resizeColumnsToContents();
}
