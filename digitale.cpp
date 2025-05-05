#include "digitale.h"

Digitale::Digitale(int s, QObject *parent) : Formato{parent}, sizeMB(s) {}

// Implementazione del getter per sizeMB
int Digitale::getSizeMB() const {
    return sizeMB;
}

