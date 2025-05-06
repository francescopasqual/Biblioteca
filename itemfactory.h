#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"      // Include l'header della classe base Item
#include "libro.h"     // Include l'header di Libro
#include "film.h"      // Include l'header di Film
#include "vinile.h"    // Include l'header di Vinile
#include <string>      // Necessario per std::string
#include <vector>      // Necessario per std::vector
#include <QObject>     // Per il parent QObject
#include <QDebug>     // Per qDebug

class ItemFactory
{
public:

    // Metodo statico per creare un Libro* (restituisce Item*)
    static Item* createLibro(std::string titolo,
                             std::string autore,
                             std::string genere,
                             int anno,
                             int copie,
                             int prestiti,
                             int pagine, // Parametro specifico per Libro
                             QObject* parent = nullptr);

    // Metodo statico per creare un Film* (restituisce Item*)
    static Item* createFilm(std::string titolo,
                            std::string regista,
                            std::string genere,
                            int anno,
                            int copie,
                            int prestiti,
                            int durata, // Parametro specifico per Film
                            std::string attore_principale, // Parametro specifico per Film
                            QObject* parent = nullptr);

    // Metodo statico per creare un Vinile* (restituisce Item*)
    static Item* createVinile(std::string titolo,
                              std::string performer,
                              std::string genere,
                              int anno,
                              int copie,
                              int prestiti,
                              int numeroTracce, // Parametro specifico per Vinile
                              int durataTotale, // Parametro specifico per Vinile
                              QObject* parent = nullptr);

private:
    // Impedisce l'istanziazione della Factory
    ItemFactory() = delete;
};

#endif // ITEMFACTORY_H
