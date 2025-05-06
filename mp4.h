#ifndef MP4_H
#define MP4_H

#include "digitale.h"
#include <string>
#include <QDebug>

class Mp4 : public Digitale
{
    Q_OBJECT // Aggiungi Q_OBJECT

private:
    int durata;
public:
    explicit Mp4(int s, int d, QObject *parent = nullptr);
    std::string descrizione() const override; // Implementazione in Mp4
    int getDurata() const;
};

#endif // MP4_H
