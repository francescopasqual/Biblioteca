#include "film.h"
#include <iostream>

// Costruttore
Film::Film(const string& id, const string& t, const string& regista, const string& genere, const string& an,
           unsigned int c, unsigned int p, const std::vector<Formato*>& formati, int d, const string& ap, QObject* parent)
    // Chiama il costruttore della classe base Item
    : Item(id, t, regista, genere, an, c, p, formati, parent),
    durata(d),
    attore_principale(ap)
{}

// Implementazione dei getter
int Film::getDurata() const
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

