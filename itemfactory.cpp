#include "itemfactory.h"
#include <QDebug> // Per debugging

// Implementazione del metodo statico per creare un Libro
Item* ItemFactory::createLibro(std::string titolo,
                               std::string autore,
                               std::string genere,
                               int anno,
                               int copie,
                               int prestiti,
                               int pagine,
                               QObject* parent)
{
    qDebug() << "ItemFactory: Creazione Libro:" << QString::fromStdString(titolo);
    // Chiamata diretta al costruttore di Libro
    return new Libro(titolo, autore, genere, anno, copie, prestiti, pagine, parent);
}

// Implementazione del metodo statico per creare un Film
Item* ItemFactory::createFilm(std::string titolo,
                              std::string regista,
                              std::string genere,
                              int anno,
                              int copie,
                              int prestiti,
                              int durata,
                              std::string attore_principale,
                              QObject* parent)
{
    qDebug() << "ItemFactory: Creazione Film:" << QString::fromStdString(titolo);
    // Chiamata diretta al costruttore di Film
    return new Film(titolo, regista, genere, anno, copie, prestiti, durata, attore_principale, parent);
}

// Implementazione del metodo statico per creare un Vinile
Item* ItemFactory::createVinile(std::string titolo,
                                std::string performer,
                                std::string genere,
                                int anno,
                                int copie,
                                int prestiti,
                                int numeroTracce,
                                int durataTotale,
                                QObject* parent)
{
    qDebug() << "ItemFactory: Creazione Vinile:" << QString::fromStdString(titolo);
    // Chiamata diretta al costruttore di Vinile
    return new Vinile(titolo, performer, genere, anno, copie, prestiti, numeroTracce, durataTotale, parent);
}
