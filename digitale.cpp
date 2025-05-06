#include "digitale.h"
#include <QDebug>

Digitale::Digitale(unsigned int s, QObject *parent) : Formato(parent), sizeMB(s) {
    qDebug() << "Chiamato costruttore di Digitale con sizeMB:" << s;
}

Digitale::~Digitale() {
    qDebug() << "Chiamato distruttore di Digitale";
}

unsigned int Digitale::getSizeMB() const {
    qDebug() << "Chiamato getSizeMB() in Digitale";
    return sizeMB;
}

bool Digitale::richiedeConnessione() const {
    qDebug() << "Chiamato richiedeConnessione() in Digitale";
    return false; // Di default, non richiede connessione (sovrascrivibile nelle classi derivate)
}
