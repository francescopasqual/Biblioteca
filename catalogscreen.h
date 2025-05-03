#ifndef CATALOGSCREEN_H
#define CATALOGSCREEN_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

class CatalogScreen : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout* mainLayout;

    //introduzione
    QLabel* welcomeLabel;


    //barra di ricerca
    QLineEdit* searchBar; //barra di ricerca
    QPushButton* searchButton; //pulsante per avviare la ricerca
    QHBoxLayout* searchLayout; //layout barra e pulsante
    QWidget* searchWidget; //widget ricerca globale

    //widget categorie complessivo
    QWidget* categorieWidget;
    QVBoxLayout* categorieLayout;
    //categoria => totale 3*ciascun_Elemento

    QWidget* bookWidget; //cat + imm
    QHBoxLayout* bookLayout;
    QLabel* bookImageLabel;
    QPixmap* bookImage;
    QPushButton* bookButton; //categoria effettiva
    //abbellire

    QWidget* filmWidget;
    QHBoxLayout* filmLayout;
    QLabel* filmImageLabel;
    QPixmap* filmImage;
    QPushButton* filmButton;

    QWidget* vinylWidget;
    QHBoxLayout* vinylLayout;
    QLabel* vinylImageLabel;
    QPixmap* vinylImage;
    QPushButton* vinylButton;

public:

    CatalogScreen(QWidget *parent = nullptr);
    ~CatalogScreen();

    // Mostra un messaggio di errore
    void showErrorMessage(const QString &message);

signals:

    // Segnale emesso quando l'utente richiede di cercare un elemento
    void globalSearchRequested(const QString& searchTerm);

    // Segnale emesso quando l'utente seleziona una categoria
    void categorySelected(const QString& category);


private slots:

    // Slot per gestire il clic sul pulsante di ricerca
    void onSearchButtonClicked();

    // Slot per gestire il clic sui pulsanti delle categorie
    void onBookButtonClicked();
    void onFilmButtonClicked();
    void onVinylButtonClicked();
};

#endif // CATALOGSCREEN_H
