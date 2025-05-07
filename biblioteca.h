#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <QObject>
#include <vector>
#include <string>
#include <QDebug>
#include "item.h"
#include "libro.h"
#include "film.h"
#include "vinile.h"
#include "itemfactory.h"


class Biblioteca : public QObject
{
    Q_OBJECT

private:
    std::vector<Item*> catalogo;

public:
    // Costruttore e distruttore
    Biblioteca(QObject *parent = nullptr);
    ~Biblioteca();

    // Metodi di gestione del catalogo
    void addItem(Item* new_item);
    void removeItem(Item* item);
    std::vector<Item*> getCatalogo() const;

    // Metodi di ricerca generici
    std::vector<Item*> searchByTitle(const string& titolo) const;
    std::vector<Item*> searchByYear(unsigned int anno) const;
    std::vector<Item*> searchByGenre(const string& genere) const;
    std::vector<Item*> searchByCreator(const string& creatore) const;

    // Funzioni di prestito
    bool prestaItem(Item* item);
    bool restituisciItem(Item* item);

    // Nuovo metodo che utilizza la factory per creare e aggiungere un item
    Item* createAndAddItem(
        ItemType type,
        const string& id,
        const string& titolo,
        const string& creatore,
        unsigned int anno,
        const string& genere,
        unsigned int copie,
        const ItemSpecificParams& specificParams,
        const std::vector<Formato*>& formati = {}
        );



signals:
    void itemAdded(Item* item);
    void itemRemoved(Item* item);
    void itemStateChanged(Item* item);
};

#endif // BIBLIOTECA_H
