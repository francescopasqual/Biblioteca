#include "fisico.h"
#include <QDebug>

Fisico::Fisico(QObject *parent) : Formato(parent) {
    qDebug() << "Chiamato costruttore di Fisico";
}


bool Fisico::richiedeSpazioFisico() const {
    qDebug() << "Chiamato richiedeSpazioFisico() in Fisico";
    return true; // I formati fisici richiedono sempre spazio fisico
}
