#ifndef DIGITALE_H
#define DIGITALE_H

#include "formato.h"

class Digitale : public Formato
{
public:
    explicit Digitale(int s, QObject *parent = nullptr);
    virtual ~Digitale() = default;

private:
    int sizeMB;
};

#endif // DIGITALE_H
