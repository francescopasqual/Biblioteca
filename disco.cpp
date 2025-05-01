#include "disco.h"

Disco::Disco(int d, QObject *parent)
    : Fisico{parent}, durata(d)
{}

std::string Disco::descrizione() const
{
    return "Formato disco";
}
