#ifndef CARTACEO_H
#define CARTACEO_H

#include "fisico.h"

class Cartaceo : public Fisico
{
public:
    Cartaceo(QObject *parent = nullptr);
    std::string descrizione() const override;

};

#endif // CARTACEO_H
