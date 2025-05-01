#include "catalogwindow.h"

CatalogWindow::CatalogWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //central widget
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    //layout principale
    mainLayout = new QVBoxLayout(central);
    setWindowTitle("Catalogo");

    mainLayout->addSpacing(40); // aggiunge spazio fisso sopra la label
    //label introduttiva
    welcomeLabel = new QLabel("Ricerca all'interno di tutto il catalogo oppure scegli una categoria in cui navigare");
    mainLayout->addWidget(welcomeLabel,0, Qt::AlignTop | Qt::AlignCenter);
    QFont welcomeFont = welcomeLabel->font(); // Ottieni il font attuale
    welcomeFont.setPointSize(welcomeFont.pointSize() + 8); // Aumenta la dimensione del font
    welcomeFont.setBold(true); // Rendi il testo in grassetto
    welcomeLabel->setFont(welcomeFont); // Applica il font modificato

    //RICERCA
    mainLayout->addSpacing(60);
    searchWidget = new QWidget(this);
    searchLayout = new QHBoxLayout(searchWidget);
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Ricerca globalmente nel catalogo...");
    searchButton = new QPushButton("Ricerca", this);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(searchButton);
    //searchWidget->setLayout(searchLayout);
    mainLayout->addWidget(searchWidget);

    //CATEGORIA LIBRI
    bookWidget = new QWidget(this);
    bookLayout = new QHBoxLayout(bookWidget);
    bookButton = new QPushButton("Libri, EBook, Audiolibri", this);
    bookImageLabel = new QLabel(this);
    //bookImage(../.../percorso);

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
    //mainLayout->addWidget(bookWidget, 0, Qt::AlignCenter);


    // CATEGORIA FILM
    filmWidget = new QWidget(this);
    filmLayout = new QHBoxLayout(filmWidget);
    filmImageLabel = new QLabel(this);
    // filmImage(":/icons/film_icon.png");
    // if (!filmImage.isNull()) {
    //     filmImageLabel->setPixmap(filmIcon.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //     filmImageLabel->setAlignment(Qt::AlignCenter);
    // } else {
    //     filmImageLabel->setText("Immagine non trovata");
    //     filmImageLabel->setAlignment(Qt::AlignCenter);
    // }

    filmButton = new QPushButton("Film e Documentari", this);
    // filmButton->setFixedSize(200, 50);
    filmLayout->addWidget(filmImageLabel);
    filmLayout->addWidget(filmButton);
    //mainLayout->addWidget(filmWidget, 0, Qt::AlignCenter);


    // CATEGORIA VINILI
    vinylWidget = new QWidget(this);
    vinylLayout = new QHBoxLayout(vinylWidget);
    vinylImageLabel = new QLabel(this);
    // vinylImage(":/icons/vinyl_icon.png");
    // if (!vinylImage.isNull()) {
    //     vinylImageLabel->setPixmap(vinylIcon.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //     vinylImageLabel->setAlignment(Qt::AlignCenter);
    // } else {
    //     vinylImageLabel->setText("Immagine non trovata");
    //     vinylImageLabel->setAlignment(Qt::AlignCenter);
    // }
    vinylButton = new QPushButton("Vinili e Musica", this);
    // vinylButton->setFixedSize(200, 50);

    vinylLayout->addWidget(vinylImageLabel);
    vinylLayout->addWidget(vinylButton);
    //mainLayout->addWidget(vinylWidget, 0, Qt::AlignCenter);
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
    connect(searchButton, &QPushButton::clicked, this, &CatalogWindow::onSearchButtonClicked);
    connect(bookButton, &QPushButton::clicked, this, &CatalogWindow::onBookButtonClicked);
    connect(filmButton, &QPushButton::clicked, this, &CatalogWindow::onFilmButtonClicked);
    connect(vinylButton, &QPushButton::clicked, this, &CatalogWindow::onVinylButtonClicked);
}

CatalogWindow::~CatalogWindow()
{
    // Distruggere tutto quello allocato con new
    delete mainLayout;
    delete welcomeLabel;
    delete searchBar;
    delete searchButton;
    delete searchLayout;
    delete searchWidget;
    delete categorieWidget;
    delete categorieLayout;
    delete bookWidget;
    delete bookLayout;
    delete bookImageLabel;
    delete bookImage;
    delete bookButton;
    delete filmWidget;
    delete filmLayout;
    delete filmImageLabel;
    delete filmImage;
    delete filmButton;
    delete vinylWidget;
    delete vinylLayout;
    delete vinylImageLabel;
    delete vinylImage;
    delete vinylButton;
}

void CatalogWindow::showErrorMessage(const QString& message)
{
    QMessageBox::critical(this, "Errore", message);
}


void CatalogWindow::onSearchButtonClicked()
{
    QString searchTerm = searchBar->text();
    emit globalSearchRequested(searchTerm);

    //la view non deve fare la ricerca effettiva e non deve cambiare la schermaa
}

void CatalogWindow::onBookButtonClicked()
{
    emit categorySelected("Libri");
}

void CatalogWindow::onFilmButtonClicked()
{
    emit categorySelected("Film");
}

void CatalogWindow::onVinylButtonClicked()
{
    emit categorySelected("Vinili");
}



