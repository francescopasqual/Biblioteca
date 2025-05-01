#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QWidget>
#include <QHBoxLayout>

class LoginWindow : public QMainWindow
{
    Q_OBJECT

private:

    QVBoxLayout* mainLayout; //layout esterno
    QVBoxLayout* loginLayout; //layout centrale per login
    QHBoxLayout* usernameLayout; //layout per username (dentro login)
    QHBoxLayout* passwordLayout; //layout per password (dentro login)

    QWidget* loginWidget;
    QWidget* usernameWidget;
    QWidget* passwordWidget;

    //messaggio di benvenuto
    QLabel* welcomeLabel;

    //Elementi login
    QLabel* usernameLabel;
    QLineEdit* usernameInput;
    QLabel* passwordLabel;
    QLineEdit* passwordInput;
    QPushButton* loginButton;


public:

    LoginWindow(QWidget *parent = nullptr);

    void showErrorMessage(const QString& message);

signals:

    // Segnale emesso quando l'utente richiede di accedere
    void loginRequested(const QString& username, const QString& password);

private slots:

    // Slot per gestire il clic sul pulsante di login
    void onLoginButtonClicked();


};

#endif // LOGINWINDOW_H
