#include "libro.h"
#include <iostream> // Necessario per usare std::cout, std::endl, std::string

//costruttore
Libro::Libro(std::string t, std::string autore, std::string genere, int an, int c, int p, int pag, QObject* parent)
    // Chiama il costruttore della classe base Item
    : Item(t, autore, genere, an, c, p, parent),
    pagine(pag) // Inizializza il membro specifico di Libro
{}

// Implementazione del metodo virtuale showInfo() per Libro
void Libro::showInfo() const
{
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni (Titolo, Autore, Genere, Anno, Copie)
    Item::showInfo();
    // Stampa le informazioni specifiche del Libro
    std::cout << "Pagine: " << pagine << std::endl;
}

// Implementazione del getter per le pagine (metodo specifico di Libro)
int Libro::getPagine() const
{
    return pagine;
}

// Implementazione del metodo virtuale getTipoCreatore() per Libro
std::string Libro::getTipoCreatore() const
{
    return "Autore"; // Specifica la dicitura per i libri
}
