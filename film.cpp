#include "film.h"
#include <iostream> // Necessario per usare std::cout, std::endl

// costruttore
int Film::getDurata() const
{
    return durata;
}

string Film::getAttore_principale() const
{
    return attore_principale;
}

Film::Film(std::string t, std::string regista, std::string genere, int an, int c, int p, int d, std::string ap, QObject* parent)
    // Chiama il costruttore della classe base Item, passando il regista come "creatore"
    : Item(t, regista, genere, an, c, p, parent), durata(d), attore_principale(ap)
{
    // Non ci sono membri specifici del Film da inizializzare in questo esempio semplice
}

string Film::getTipoCreatore() const
{
    return "Regista"; // Specifica la dicitura per i film
}

// Implementazione del metodo virtuale showInfo() per Film
void Film::showInfo() const
{
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni (Titolo, Regista, Genere, Anno, Copie)
    Item::showInfo();
    std::cout << "Durata: " << durata << " minuti" << std::endl;
}

