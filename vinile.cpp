#include "vinile.h"
#include <iostream>

// Costruttore
Vinile::Vinile(const string& id, const string& t, const string& performer, const string& genere, const string& an,
               unsigned int c, unsigned int p, const std::vector<Formato*>& formati, int nt, int dt, QObject* parent)
    // Chiama il costruttore della classe base Item
    : Item(id, t, performer, genere, an, c, p, formati, parent),
    numeroTracce(nt),
    durataTotale(dt)
{}

// Implementazione dei getter
int Vinile::getNumeroTracce() const
{
    return numeroTracce;
}

int Vinile::getDurataTotale() const
{
    return durataTotale;
}

// Implementazione del metodo virtuale showInfo() per Vinile
void Vinile::showInfo() const
{
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni
    Item::showInfo();
    // Stampa le informazioni specifiche del Vinile
    std::cout << "Numero tracce: " << numeroTracce << std::endl;
    std::cout << "Durata totale: " << durataTotale << " minuti" << std::endl;
}

