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

signals:
    void itemAdded(Item* item);
    void itemRemoved(Item* item);
    void itemStateChanged(Item* item);
};

#endif // BIBLIOTECA_H
