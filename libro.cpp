#include "libro.h"
#include <iostream>

// Costruttore
Libro::Libro(const string& id, const string& t, const string& autore, const string& genere, const string& an,
             unsigned int c, unsigned int p, const std::vector<Formato*>& formati, int pag, QObject* parent)
    // Chiama il costruttore della classe base Item
    : Item(id, t, autore, genere, an, c, p, formati, parent),
    pagine(pag) // Inizializza il membro specifico di Libro
{}

// Implementazione del metodo virtuale showInfo() per Libro
void Libro::showInfo() const
{
    // Chiama il metodo showInfo() della classe base per stampare le informazioni comuni
    Item::showInfo();
    // Stampa le informazioni specifiche del Libro
    std::cout << "Pagine: " << pagine << std::endl;
}

// Implementazione del getter per le pagine (metodo specifico di Libro)
int Libro::getPagine() const
{
    return pagine;
}

