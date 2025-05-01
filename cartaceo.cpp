#include "cartaceo.h"

Cartaceo::Cartaceo(QObject *parent)
    : Fisico{parent}{}

std::string Cartaceo::descrizione() const
{
    return "Formato cartaceo";
}
