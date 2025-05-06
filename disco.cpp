#include "disco.h"
#include <string> // Per std::to_string

Disco::Disco(unsigned int durata, QObject *parent)
    : Fisico(parent), durata(durata) {
    qDebug() << "Chiamato costruttore di Disco con durata:" << durata;
}

Disco::~Disco() {
    qDebug() << "Chiamato distruttore di Disco";
}

std::string Disco::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Disco";
    return "Formato disco (Durata: " + std::to_string(durata) + " minuti)";
}

unsigned int Disco::getDurata() const {
    qDebug() << "Chiamato getDurata() in Disco";
    return durata;
}
