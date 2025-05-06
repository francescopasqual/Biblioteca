#ifndef EPUB_H
#define EPUB_H

#include "digitale.h"
#include <string>
#include <QDebug>

class Epub : public Digitale
{
    Q_OBJECT

public:
    explicit Epub(unsigned int sizeMB, QObject *parent = nullptr);
    ~Epub() override;

    std::string descrizione() const override;

    // Override per la funzionalità specifica di Epub
    bool richiedeConnessione() const override;
};

#endif // EPUB_H
