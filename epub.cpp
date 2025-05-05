#include "epub.h"
#include <string> // Per std::to_string

Epub::Epub(int s, QObject *parent) : Digitale(s, parent) {}

// Implementazione completa di descrizione() in Epub
std::string Epub::descrizione() const
{
    // Usa il getter per sizeMB ereditato da Digitale
    return "Formato EPUB (Dimensioni: " + std::to_string(getSizeMB()) + " MB)";
}
