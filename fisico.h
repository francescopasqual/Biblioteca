#ifndef FISICO_H
#define FISICO_H

#include "formato.h"
#include <string>

class Fisico : public Formato
{
    Q_OBJECT

public:
    explicit Fisico(QObject *parent = nullptr);
    virtual ~Fisico() = default;

    // Mantiene il metodo descrizione come virtuale puro
    std::string descrizione() const override = 0;

    // Aggiunto metodo comune a tutti i formati fisici
    virtual bool richiedeSpazioFisico() const;
};

#endif // FISICO_H
