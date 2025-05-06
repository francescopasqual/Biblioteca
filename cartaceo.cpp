#include "cartaceo.h"
#include <string>

Cartaceo::Cartaceo(std::string isbn, QObject *parent)
    : Fisico{parent}, isbn(isbn) {
    qDebug() << "Chiamato costruttore di Cartaceo con ISBN:";
}

std::string Cartaceo::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Cartaceo";
    // Include l'ISBN nella descrizione
    return "Formato cartaceo (ISBN: " + isbn + ")";
}

std::string Cartaceo::getIsbn() const {
    qDebug() << "Chiamato getIsbn() in Cartaceo";
    return isbn;
}
