#include "film.h"
#include <iostream>

//Costruttore
Film::Film(const string &id, const string &t, const string &cr, unsigned int an, const string &g, unsigned int c,
           unsigned int p, unsigned int dur, const string &attore, QObject *parent)
    : Item(id, t, cr, an, g, c, p, parent),
      durata(dur),
      attore_principale(attore)
{
    //il vettore dei formati viene creato vuoto di default
}

// Implementazione dei getter
unsigned int Film::getDurata() const
{
    return durata;
}

string Film::getAttore_principale() const
{
    return attore_principale;
}


// Implementazione del metodo virtuale showInfo() per Film
void Film::showInfo() const
{
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni
    Item::showInfo();
    // Stampa le informazioni specifiche del Film
    std::cout << "Durata: " << durata << " minuti" << std::endl;
    std::cout << "Attore principale: " << attore_principale << std::endl;
}

