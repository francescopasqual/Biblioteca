#include "epub.h"


Epub::Epub(int s, QObject *parent) : Digitale(s,parent) {}

std::string Epub::descrizione() const
{
    return "Formato EPUB";
}
