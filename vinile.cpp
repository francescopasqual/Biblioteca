#include "vinile.h"

//costruttore
int Vinile::getNumeroTracce() const
{
    return numeroTracce;
}

int Vinile::getDurataTotale() const
{
    return durataTotale;
}

Vinile::Vinile(string t, string performer, string genere, int an, int c, int p, int nt, int dt, QObject* parent)
    : Item(t, performer, genere, an, c, p, parent),
    numeroTracce(nt), durataTotale(dt)
{
}

string Vinile::getTipoCreatore() const
{
    return "Performer"; // Specifica la dicitura per i vinili
}

// Implementazione del metodo virtuale showInfo() per Vinile
void Vinile::showInfo() const
{
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni (Titolo, Performer, Genere, Anno, Copie)
    Item::showInfo();
    // Stampa le informazioni specifiche del Vinile
    std::cout << "Numero tracce: " << numeroTracce << std::endl;
    std::cout << "Durata totale: " << durataTotale << " minuti" << std::endl;
}

