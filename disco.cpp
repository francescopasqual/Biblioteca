#include "disco.h"
#include <string> // Per std::to_string

Disco::Disco(int d, QObject *parent) : Fisico{parent}, durata(d) {}

std::string Disco::descrizione() const
{
    return "Formato disco (Durata: " + std::to_string(durata) + " minuti)";
}

int Disco::getDurata() const {
    return durata;
}
