#ifndef DIGITALE_H
#define DIGITALE_H

#include "formato.h"
#include <string>

class Digitale : public Formato
{
    Q_OBJECT

private:
    unsigned int sizeMB;

public:
    explicit Digitale(unsigned int s = 0, QObject *parent = nullptr);
    virtual ~Digitale() = default;

    // Mantiene descrizione come virtuale pura
    std::string descrizione() const override = 0;

    // Getter per sizeMB
    unsigned int getSizeMB() const;

    // Aggiunta funzionalità comune ai formati digitali
    virtual bool richiedeConnessione() const;
};

#endif // DIGITALE_H
