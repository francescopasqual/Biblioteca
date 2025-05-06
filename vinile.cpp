#include "vinile.h"

int Vinile::getNumeroTracce() const
{
    qDebug() << "Chiamato getNumeroTracce() in Vinile";
    return numeroTracce;
}

int Vinile::getDurataTotale() const
{
    qDebug() << "Chiamato getDurataTotale() in Vinile";
    return durataTotale;
}

Vinile::Vinile(string t, string performer, string genere, int an, int c, int p, int nt, int dt, QObject* parent)
    : Item(t, performer, genere, an, c, p, parent),
    numeroTracce(nt), durataTotale(dt)
{
    qDebug() << "Chiamato costruttore di Vinile";
}

string Vinile::getTipoCreatore() const
{
    qDebug() << "Chiamato getTipoCreatore() in Vinile";
    return "Performer"; // Specifica la dicitura per i vinili
}

// Implementazione del metodo virtuale showInfo() per Vinile
void Vinile::showInfo() const
{
    qDebug() << "Chiamato showInfo() in Vinile";
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni (Titolo, Performer, Genere, Anno, Copie)
    Item::showInfo();
    // Stampa le informazioni specifiche del Vinile
    std::cout << "Numero tracce: " << numeroTracce << std::endl;
    std::cout << "Durata totale: " << durataTotale << " minuti" << std::endl;
}

