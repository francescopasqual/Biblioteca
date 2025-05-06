#include "vinile.h"
#include <iostream>

// Costruttore
Vinile::Vinile(const string &id, const string &t, const string &cr, unsigned int an, const string &g, unsigned int c,
               unsigned int p, unsigned int numTracce, unsigned int durTotale, QObject *parent)
    : Item(id, t, cr, an, g, c, p, parent),
      numeroTracce(numTracce),
      durataTotale(durTotale)
{
    //il vettore dei formati viene creato vuoto di default
}

// Implementazione dei getter
unsigned int Vinile::getNumeroTracce() const
{
    return numeroTracce;
}

unsigned int Vinile::getDurataTotale() const
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

