#ifndef FISICO_H
#define FISICO_H

#include "formato.h"

class Fisico : public Formato
{

public:

    Fisico(QObject *parent = nullptr);
    virtual ~Fisico() = default;
    std::string descrizione() const override = 0;
};

#endif // FISICO_H
