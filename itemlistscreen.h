#ifndef ITEMLISTSCREEN_H
#define ITEMLISTSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem> // Necessario per la firma dello slot itemClicked
#include <vector> // Necessario per std::vector
#include "item.h" // Necessario per Item*
#include <QHeaderView> // Necessario per QHeaderView
#include <QDebug> // Necessario per qDebug()
#include <QVariant> // Necessario per QVariant

// Registra Item* nel sistema dei metatipi di Qt (come discusso, meglio metterlo altrove)
// Richiede #include <QVariant> e #include <QDataStream> dove è definito
// Q_DECLARE_METATYPE(Item*)

//per finestra di visualizzazione di una lista di Item

class ItemListScreen : public QWidget
{
    Q_OBJECT

private:

    //layout
    QVBoxLayout* mainLayout;
    QHBoxLayout* upperSectionLayout;

    //widget
    QTableWidget* itemTable;
    QWidget* upperSectionWidget;
    QLabel* landingLabel;
    QPushButton* backButton;


public:
    explicit ItemListScreen(QWidget *parent = nullptr);
    ~ItemListScreen();

    // Metodo pubblico che il Controller chiamerà per passare i dati e il testo del titolo
    void toInsertItems(const std::vector<Item*>& items, const QString& searchTermOrCategory);

signals:
    // Segnale emesso quando l'utente seleziona un item dalla tabella
    void itemSelected(Item* selectedItem); // Il segnale deve passare il puntatore Item*

    // Segnale emesso quando l'utente clicca sul bottone Indietro
    void backRequested(); // Nuovo segnale per il bottone Indietro


private slots:
    // Slot che gestisce il clic su un item della tabella
    // La firma deve corrispondere al segnale QTableWidget::itemClicked
    void onItemClicked(QTableWidgetItem* item); // La firma deve includere QTableWidgetItem*

    // Slot che gestisce il clic sul bottone Indietro
    void onBackButtonClicked(); // Nuovo slot per il bottone Indietro

};

#endif // ITEMLISTSCREEN_H
