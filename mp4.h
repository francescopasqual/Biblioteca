#ifndef MP4_H
#define MP4_H

#include "digitale.h"
#include <string>
#include <QDebug>

class Mp4 : public Digitale
{
    Q_OBJECT

private:
    unsigned int durata;

public:
    explicit Mp4(unsigned int sizeMB, unsigned int durata, QObject *parent = nullptr);
    ~Mp4() override = default;


    std::string descrizione() const override;
    unsigned int getDurata() const;

    // Override per la funzionalità specifica di Mp4
    bool richiedeConnessione() const override;
};

#endif // MP4_H
