#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <QObject>
#include <vector>
#include "item.h"
#include <QDebug>
#include <QDebug>

class Biblioteca : public QObject
{
    Q_OBJECT

private:

    std::vector<Item*> catalogo;

public:
    // Constructor
    Biblioteca(QObject *parent = nullptr);

    //Distruttore
    ~Biblioteca();

    //aggiungere un item al catalogo
    void addItem(Item* new_item);

    //rimuovere un item dal catalogo
    void removeItem(Item* item);

    //restituire il catalogo
    std::vector<Item*> getCatalogo() const;

    //ricerca per titolo generale
    std::vector<Item*> searchByTitle(string titolo) const;

    //ricerca per anno generale
    std::vector<Item*> searchByYear(int anno) const;

    //LIBRI
    //ricerca per genere
    std::vector<Item*> searchByGenre(string genere) const;
    //ricerca per autore
    std::vector<Item*> searchByAuthor(string autore) const;

    //FILM
    //ricerca per regista
    std::vector<Item*> searchByRegista(string regista) const;
    //ricerca per genere
    std::vector<Item*> searchByGenere(string genere) const;

    //VINILI
    //ricerca per performer
    std::vector<Item*> searchByPerformer(string performer) const;
    //ricerca per genere_musicale
    std::vector<Item*> searchByGenereMusicale(string genere) const;


    //FUNZIONI DI PRESTITO
    bool prestaItem(Item* item);

    bool restituisciItem(Item* item);




    //persistenza dei dati con JSON

signals:
};

#endif // BIBLIOTECA_H
