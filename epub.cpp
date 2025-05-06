#include "epub.h"
#include <string> // Per std::to_string

Epub::Epub(unsigned int sizeMB, QObject *parent)
    : Digitale(sizeMB, parent) {
    qDebug() << "Chiamato costruttore di Epub con sizeMB:" << sizeMB;
}

Epub::~Epub() {
    qDebug() << "Chiamato distruttore di Epub";
}

std::string Epub::descrizione() const
{
    qDebug() << "Chiamato descrizione() in Epub";
    return "Formato EPUB (Dimensioni: " + std::to_string(getSizeMB()) + " MB)";
}

bool Epub::richiedeConnessione() const
{
    qDebug() << "Chiamato richiedeConnessione() in Epub";
    return false; // Gli EPUB non richiedono connessione una volta scaricati
}
