#ifndef CARTACEO_H
#define CARTACEO_H

#include "fisico.h"
#include <string>
#include <QDebug>

class Cartaceo : public Fisico
{
    Q_OBJECT

private:
    std::string tipo_copertina;

public:
    explicit Cartaceo(const std::string& tc, QObject *parent = nullptr);


    std::string descrizione() const override;
    std::string getTipoCopertina() const;
};

#endif // CARTACEO_H
