#ifndef CARTACEO_H
#define CARTACEO_H

#include "fisico.h"
#include <string>
#include <QDebug>
class Cartaceo : public Fisico
{
    Q_OBJECT

private:
    std::string isbn;

public:
    explicit Cartaceo(std::string isbn, QObject *parent = nullptr);
    std::string descrizione() const override;

    std::string getIsbn() const;

};

#endif // CARTACEO_H
