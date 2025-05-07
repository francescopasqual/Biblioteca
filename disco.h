#ifndef DISCO_H
#define DISCO_H

#include "fisico.h"
#include <string>
#include <QDebug>

class Disco : public Fisico
{
    Q_OBJECT

private:
    unsigned int bpm;

public:
    explicit Disco(unsigned int bpm, QObject *parent = nullptr);


    std::string descrizione() const override;
    unsigned int getbpm() const;
};

#endif // DISCO_H
