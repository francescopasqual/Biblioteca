#include "epub.h"
#include <string> // Per std::to_string

Epub::Epub(int s, QObject *parent) : Digitale(s, parent) {
    qDebug() << "Chiamato costruttore di Epub con sizeMB:" << s;
}

// Implementazione completa di descrizione() in Epub
std::string Epub::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Epub";
    // Usa il getter per sizeMB ereditato da Digitale
    return "Formato EPUB (Dimensioni: " + std::to_string(getSizeMB()) + " MB)";
}
