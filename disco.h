#ifndef DISCO_H
#define DISCO_H

#include "fisico.h"

class Disco : public Fisico
{
public:

    Disco(int d, QObject *parent = nullptr);
    std::string descrizione() const override;

private:
    int durata;
};

#endif // DISCO_H
