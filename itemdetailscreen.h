#ifndef ITEMDETAILSCREEN_H
#define ITEMDETAILSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include "item.h"
#include <QGroupBox>


//mostra informazioni di dettaglio per uno specifico item

class ItemDetailScreen : public QWidget
{
    Q_OBJECT

private:
    Item* currentItem; // Puntatore all'item corrente

    //widget contenitivi
    QWidget* itemWidget; //details + formati
    QGroupBox* detailsWidget;
    QGroupBox* formatsWidget;
    QGroupBox* buttonsWidget;

    //layout
    QVBoxLayout* mainLayout;
    QVBoxLayout* itemLayout;
    QFormLayout* detailsLayout;
    QVBoxLayout* formatsLayout;
    QHBoxLayout* buttonsLayout;


    //details widget
    //per le info
    QLabel* titleLabel;
    QLabel* creatorLabel;
    QLabel* genreLabel;
    QLabel* yearLabel;
    QLabel* copiesLabel;
    QLabel* loansLabel;
    QLabel* availableLabel;

    QLabel *creatorValueLabel;
    QLabel *genreValueLabel;
    QLabel *yearValueLabel;
    QLabel *copiesValueLabel;
    QLabel *loansValueLabel;
    QLabel *availabilityValueLabel;

    //per i formati
    QLabel* formatsTitle;

    //pulsanti finali
    QPushButton* exitButton;
    QPushButton* loanButton;
    QPushButton* keepButton;


    //funzione helper
    /* Itera su tutti gli elementi del layout e li cancella.
     * In questo modo poi possiamo procedere a inserire dinamicamente le label per ciascun formato trovato di quell'item
     */

    void clearFormatsLayout();


public:

    ItemDetailScreen(QWidget *parent = nullptr);
    ~ItemDetailScreen() = default;

    void displayDetails(Item* item);
    //"Label dinamiche" in questo contesto significa che:


signals:

    //riporta alla finestra in cui si era precedentemente alla ItemDetailScreen
    void exitRequest(); //emesso quando si clicca sul pulsante exit

    //emesso quando si clicca sul pulsante loan
    void loanRequest(Item* item);
    //emesso quando si clicca sul pulsante keep
    void keepRequest(Item* item);




private slots:

    void onExitButtonClicked();

    void onLoanButtonClicked();

    void onKeepButtonClicked();


};

#endif // ITEMDETAILSCREEN_H
