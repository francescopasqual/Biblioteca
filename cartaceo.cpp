#include "cartaceo.h"
#include <string>

Cartaceo::Cartaceo(const std::string& tc, QObject *parent)
    : Fisico(parent), tipo_copertina(tc) {
    qDebug() << "Chiamato costruttore di Cartaceo con tipo di copertina:" << QString::fromStdString(tc);
}



std::string Cartaceo::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Cartaceo";
    return "Formato cartaceo con copertina: " + tipo_copertina + ")";
}

std::string Cartaceo::getTipoCopertina() const {
    qDebug() << "Chiamato getIsbn() in Cartaceo";
    return tipo_copertina;
}
