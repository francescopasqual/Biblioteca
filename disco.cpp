#include "disco.h"
#include <string> // Per std::to_string

Disco::Disco(int d, QObject *parent) : Fisico{parent}, durata(d) {
    qDebug () << "Chiamato costruttore di Disco con durata:" << d;
}

std::string Disco::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Disco";
    return "Formato disco (Durata: " + std::to_string(durata) + " minuti)";
}

int Disco::getDurata() const {
    qDebug() << "Chiamato getDurata() in Disco";
    return durata;
}
