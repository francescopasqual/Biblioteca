#include "formato.h"
#include <QDebug>

Formato::Formato(QObject *parent) : QObject(parent) {
    qDebug() << "Chiamato costruttore di Formato";
}
