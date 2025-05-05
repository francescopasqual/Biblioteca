#include "mp4.h"
#include <string> // Per std::to_string


Mp4::Mp4(int s, int d, QObject *parent) : Digitale(s, parent), durata(d) {}

int Mp4::getDurata() const
{
    return durata;
}

// Implementazione completa di descrizione() in Mp4
std::string Mp4::descrizione() const
{
    // Usa il getter per sizeMB ereditato da Digitale
    return "Formato MP4 (Dimensioni: " + std::to_string(getSizeMB()) + " MB;\n"
            "Durata: "+ std::to_string(getDurata()) + " minuti;";
}
