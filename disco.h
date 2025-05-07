#ifndef DISCO_H
#define DISCO_H

#include "fisico.h"
#include <string>
#include <QDebug>

class Disco : public Fisico
{
    Q_OBJECT

private:
    unsigned int durata;

public:
    explicit Disco(unsigned int durata, QObject *parent = nullptr);


    std::string descrizione() const override;
    unsigned int getDurata() const;
};

#endif // DISCO_H
