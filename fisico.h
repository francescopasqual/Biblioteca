#ifndef FISICO_H
#define FISICO_H

#include "formato.h"

class Fisico : public Formato
{
public:
    Fisico(QObject *parent = nullptr);
    virtual ~Fisico() = default;
};

#endif // FISICO_H
