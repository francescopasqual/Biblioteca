#include "disco.h"
#include <string> // Per std::to_string

Disco::Disco(unsigned int bpm, QObject *parent)
    : Fisico(parent), bpm(bpm) {
    qDebug() << "Chiamato costruttore di Disco con bpm:" << bpm;
}


std::string Disco::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Disco";
    return "Formato disco, bpm: " + std::to_string(bpm);
}

unsigned int Disco::getbpm() const {
    qDebug() << "Chiamato getbpm() in Disco";
    return bpm;
}
