#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    //central widget
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QVBoxLayout(central);
    setWindowTitle("Login");


    //benvenuto
    welcomeLabel = new QLabel("Benvenuto Bibliotecario", this);
    QFont welcomeFont = welcomeLabel->font(); // Ottieni il font attuale
    welcomeFont.setPointSize(welcomeFont.pointSize() + 8); // Aumenta la dimensione del font
    welcomeFont.setBold(true); // Rendi il testo in grassetto
    welcomeLabel->setFont(welcomeFont); // Applica il font modificato
    //welcomeLabel->setMinimumHeight(80); replace con addspacing sul mainlayout????

    // Aggiungi il messaggio di benvenuto in alto nel layout principale
    mainLayout->addWidget(welcomeLabel, 0, Qt::AlignCenter | Qt::AlignTop);


    //login
    usernameLabel = new QLabel("Username: ", this);
    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Inserire nome utente...");
    passwordLabel = new QLabel("Password: ", this);
    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Inserire la password...");
    loginButton = new QPushButton("Accedi", this);
    passwordInput->setEchoMode(QLineEdit::Password); // Nasconde il testo password
    loginButton->setDefault(true); // Rende il pulsante di default (attivabile con Invio)

    // Configura allineamento etichette se vuoi che stiano a destra prima dell'input
    usernameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    passwordLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // Layout orizzontali per coppia Etichetta+Input
    usernameLayout = new QHBoxLayout(); // Layout orizzontale per username (non ha parent qui, verrà aggiunto a loginLayout)
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameInput);
    usernameLayout->addStretch(); // Aggiunge spazio elastico orizzontale
    usernameWidget = new QWidget(this);
    usernameWidget->setLayout(usernameLayout);

    passwordLayout = new QHBoxLayout(); // Layout orizzontale per password
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordInput);
    passwordLayout->addStretch(); // Aggiunge spazio elastico orizzontale
    passwordWidget = new QWidget(this);
    passwordWidget->setLayout(passwordLayout);


    // Layout verticale per il blocco di login (username, password, pulsante)
    loginLayout = new QVBoxLayout(); // Layout verticale per raggruppare i campi di login
    loginLayout->addWidget(usernameWidget,0, Qt::AlignCenter);
    loginLayout->addWidget(passwordWidget, 0, Qt::AlignCenter);
    loginLayout->addStretch(1);
    loginLayout->addWidget(loginButton, 0, Qt::AlignCenter); // Aggiunge il pulsante centrato orizzontalmente

    loginWidget = new QWidget(this);
    loginWidget->setLayout(loginLayout);
    loginWidget->setMinimumSize(500,150);

    mainLayout->addStretch(1);

    // Aggiungi il contenitore del form al layout principale, centrato orizzontalmente
    mainLayout->addWidget(loginWidget, 0, Qt::AlignCenter);

    // Aggiungi un altro "stretch" verticale sotto il blocco di login per spingerlo verso il centro/alto
    mainLayout->addStretch(2); // Spazio elastico 2 (insieme al primo, centra il widget intermedio)

}

void LoginWindow::onLoginButtonClicked()
{
    // Emit the loginRequested signal with the entered username and password
    emit loginRequested(usernameInput->text(), passwordInput->text());
}

void LoginWindow::showErrorMessage(const QString &message)
{
    QMessageBox::warning(this, "Errore di accesso", message);
}
