#include "cartaceo.h"
#include <string>

Cartaceo::Cartaceo(std::string isbn, QObject *parent)
    : Fisico{parent}, isbn(isbn) {}

std::string Cartaceo::descrizione() const
{
    // Include l'ISBN nella descrizione
    return "Formato cartaceo (ISBN: " + isbn + ")";
}

std::string Cartaceo::getIsbn() const {
    return isbn;
}
