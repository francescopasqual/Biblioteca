#include "cartaceo.h"
#include <string>

Cartaceo::Cartaceo(const std::string& isbn, QObject *parent)
    : Fisico(parent), isbn(isbn) {
    qDebug() << "Chiamato costruttore di Cartaceo con ISBN:" << QString::fromStdString(isbn);
}

Cartaceo::~Cartaceo() {
    qDebug() << "Chiamato distruttore di Cartaceo";
}

std::string Cartaceo::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Cartaceo";
    return "Formato cartaceo (ISBN: " + isbn + ")";
}

std::string Cartaceo::getIsbn() const {
    qDebug() << "Chiamato getIsbn() in Cartaceo";
    return isbn;
}
