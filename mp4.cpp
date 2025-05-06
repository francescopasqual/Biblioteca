#include "mp4.h"
#include <string> // Per std::to_string


Mp4::Mp4(unsigned int s, unsigned int d, QObject *parent) : Digitale(s, parent), durata(d) {
    qDebug() << "Chiamato costruttore di Mp4";
}

unsigned int Mp4::getDurata() const
{
    qDebug() << "Chiamato getDurata() in Mp4";
    return durata;
}

// Implementazione completa di descrizione() in Mp4
std::string Mp4::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Mp4";
    // Usa il getter per sizeMB ereditato da Digitale
    return "Formato MP4 (Dimensioni: " + std::to_string(getSizeMB()) + " MB;\n"
            "Durata: "+ std::to_string(getDurata()) + " minuti;";
}
