#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <string>
#include <vector>
#include "formato.h"
#include <iostream>

using std::string;
using std::cout; using std::endl;


class Item : public QObject {
    Q_OBJECT

protected:
    string ID;
    string titolo;
    string creatore; // autore/regista/performer
    unsigned int anno;
    string genere;    // Genere comune
    unsigned int copie;
    unsigned int prestiti;
    std::vector<Formato*> formati;

public:
    // Costruttore
    Item(const string& id, const string& t, const string& cr, unsigned int an, const string& g, unsigned int c, unsigned int p, QObject* parent = nullptr);

    // Distruttore virtuale
    virtual ~Item();

    virtual void showInfo() const;

    // Getter
    string getID() const;
    string getTitolo() const;
    string getCreatore() const;
    string getGenere() const;
    unsigned int getAnno() const;
    unsigned int getCopie() const;
    unsigned int getPrestiti() const;
    std::vector<Formato*> getFormati() const;

    //Inserimento dei formati: funzione a parte perchè posso aggiungerlo sia in fase di costruzione che per aggiornare un item
    void addFormato(Formato* formato);

    // Metodi per la gestione dei prestiti
    bool incrementaPrestiti();
    bool decrementaPrestiti();
    bool isAvailable() const;

    // Factory method che verrà implementato in seguito
    // static Item* create(ItemType type, ...);
};

#endif // ITEM_H
