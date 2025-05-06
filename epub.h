#ifndef EPUB_H
#define EPUB_H

#include "digitale.h"
#include <string>
#include <QDebug>

class Epub : public Digitale
{
    Q_OBJECT // Aggiungi Q_OBJECT

public:

    explicit Epub(int s, QObject *parent = nullptr);
    std::string descrizione() const override; // Implementazione in Epub
};

#endif // EPUB_H
