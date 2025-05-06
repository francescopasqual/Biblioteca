#include "libro.h"
#include <iostream>

// Costruttore
Libro::Libro(const string &id, const string &t, const string &cr, unsigned int an, const string &g, unsigned int c, unsigned int p, int pag, QObject *parent)
    : Item(id, t, cr, an, g, c, p, parent),
    pagine(pag)
{
    //il vettore dei formati viene creato vuoto di default
}


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

