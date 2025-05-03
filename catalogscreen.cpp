#include "catalogscreen.h"

CatalogScreen::CatalogScreen(QWidget *parent)
    : QWidget{parent}
{
    //layout principale
    mainLayout = new QVBoxLayout(this);
    //setLayout(mainLayout);


    mainLayout->addSpacing(40); // aggiunge spazio fisso sopra la label
    //label introduttiva
    welcomeLabel = new QLabel("Ricerca all'interno di tutto il catalogo oppure scegli una categoria in cui navigare", this);
    mainLayout->addWidget(welcomeLabel,0, Qt::AlignTop | Qt::AlignCenter);
    QFont welcomeFont = welcomeLabel->font(); // Ottieni il font attuale
    welcomeFont.setPointSize(welcomeFont.pointSize() + 8); // Aumenta la dimensione del font
    welcomeFont.setBold(true); // Rendi il testo in grassetto
    welcomeLabel->setFont(welcomeFont); // Applica il font modificato

    //RICERCA
    mainLayout->addSpacing(60);
    searchWidget = new QWidget(this);
    searchLayout = new QHBoxLayout(searchWidget);
    searchBar = new QLineEdit(searchWidget);
    searchBar->setPlaceholderText("Ricerca globalmente nel catalogo...");
    searchButton = new QPushButton("Ricerca", this);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(searchButton);
    //searchWidget->setLayout(searchLayout);
    mainLayout->addWidget(searchWidget);

    //CATEGORIA LIBRI
    bookWidget = new QWidget(this);
    bookLayout = new QHBoxLayout(bookWidget);
    bookButton = new QPushButton("Libri, EBook, Audiolibri", bookWidget);
    bookImageLabel = new QLabel(bookWidget);
    //bookImage(../.../percorso);

    // !!! QPixmap: Gestisci QPixmap come OGGETTO non puntatore se possibile, o dealloca il puntatore nel distruttore. !!!
    // Se usi QPixmap* bookImage; nel .h e lo allochi con new:
    // bookImage = new QPixmap(":/icons/book_icon.png"); // Esempio allocazione
    // if (bookImage && !bookImage->isNull()) { bookImageLabel->setPixmap(bookImage->scaled(...)); }
    // Se usi QPixmap bookImage; nel .h (non puntatore):
    // bookImage.load(":/icons/book_icon.png"); // Esempio caricamento
    // if (!bookImage.isNull()) { bookImageLabel->setPixmap(bookImage.scaled(...)); }
    // bookButton: Passa bookWidget come parent o 'this'. Meglio bookWidget.
    //settaggio immagine

    // if(!bookImage->isNull()){
    //     // Ridimensiona l'immagine se necessario (mantiene l'aspetto originale)
    //     bookImageLabel->setPixmap(bookIcon->scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //     bookImageLabel->setAlignment(Qt::AlignCenter); // Centra l'immagine nella sua label
    // }else{
    //     // Gestisci il caso in cui l'immagine non viene caricata (mostra un testo alternativo o un'icona di default)
    //     bookImageLabel->setText("Immagine non trovata");
    //     bookImageLabel->setAlignment(Qt::AlignCenter);

    // }

    bookLayout->addWidget(bookImageLabel);
    bookLayout->addWidget(bookButton);


    // CATEGORIA FILM
    filmWidget = new QWidget(this);
    filmLayout = new QHBoxLayout(filmWidget);
    filmImageLabel = new QLabel(filmWidget);
    // filmImage(":/icons/film_icon.png");
    // if (!filmImage.isNull()) {
    //     filmImageLabel->setPixmap(filmIcon.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //     filmImageLabel->setAlignment(Qt::AlignCenter);
    // } else {
    //     filmImageLabel->setText("Immagine non trovata");
    //     filmImageLabel->setAlignment(Qt::AlignCenter);
    // }

    filmButton = new QPushButton("Film e Documentari", filmWidget);
    // filmButton->setFixedSize(200, 50);
    filmLayout->addWidget(filmImageLabel);
    filmLayout->addWidget(filmButton);


    // CATEGORIA VINILI
    vinylWidget = new QWidget(this);
    vinylLayout = new QHBoxLayout(vinylWidget);
    vinylImageLabel = new QLabel(vinylWidget);
    // vinylImage(":/icons/vinyl_icon.png");
    // if (!vinylImage.isNull()) {
    //     vinylImageLabel->setPixmap(vinylIcon.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //     vinylImageLabel->setAlignment(Qt::AlignCenter);
    // } else {
    //     vinylImageLabel->setText("Immagine non trovata");
    //     vinylImageLabel->setAlignment(Qt::AlignCenter);
    // }
    vinylButton = new QPushButton("Vinili e Musica", vinylWidget);
    // vinylButton->setFixedSize(200, 50);

    vinylLayout->addWidget(vinylImageLabel);
    vinylLayout->addWidget(vinylButton);
    //mainLayout->addStretch(1);


    //racchiude i 3 widget delle categorie, li posiziona in verticale
    //!LAVORARE SU SPACING
    categorieWidget = new QWidget(this);
    categorieLayout = new QVBoxLayout(categorieWidget);
    categorieLayout->addWidget(bookWidget,0, Qt::AlignTop | Qt::AlignCenter);
    categorieLayout->addWidget(filmWidget, 0, Qt::AlignTop | Qt::AlignCenter);
    categorieLayout->addWidget(vinylWidget, 0, Qt::AlignTop | Qt::AlignCenter);

    mainLayout->addWidget(categorieWidget,0,Qt::AlignCenter);
    mainLayout->addStretch(1);

    //connect
    connect(searchButton, &QPushButton::clicked, this, &CatalogScreen::onSearchButtonClicked);
    connect(bookButton, &QPushButton::clicked, this, &CatalogScreen::onBookButtonClicked);
    connect(filmButton, &QPushButton::clicked, this, &CatalogScreen::onFilmButtonClicked);
    connect(vinylButton, &QPushButton::clicked, this, &CatalogScreen::onVinylButtonClicked);
}

CatalogScreen::~CatalogScreen()
{

}

void CatalogScreen::showErrorMessage(const QString& message)
{
    qDebug() << "CatalogScreen::showErrorMessage() called:" << message;
    QMessageBox::critical(this, "Errore", message);
}


void CatalogScreen::onSearchButtonClicked()
{
    qDebug() << "CatalogScreen::onSearchButtonClicked() called";
    QString searchTerm = searchBar->text();
    emit globalSearchRequested(searchTerm);

    //la view non deve fare la ricerca effettiva e non deve cambiare la schermaa
}

void CatalogScreen::onBookButtonClicked()
{
    qDebug() << "CatalogScreen::onBookButtonClicked() called";
    emit categorySelected("Libri");
}

void CatalogScreen::onFilmButtonClicked()
{
    qDebug() << "CatalogScreen::onFilmButtonClicked() called";
    emit categorySelected("Film");
}

void CatalogScreen::onVinylButtonClicked()
{
    qDebug() << "CatalogScreen::onVinylButtonClicked() called";
    emit categorySelected("Vinili");
}



