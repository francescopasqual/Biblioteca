#ifndef DISCO_H
#define DISCO_H

#include "fisico.h"

class Disco : public Fisico
{

private:
    int durata;

public:

    Disco(int d, QObject *parent = nullptr);
    std::string descrizione() const override;

    int getDurata() const;
};

#endif // DISCO_H
