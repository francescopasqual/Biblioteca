#ifndef EPUB_H
#define EPUB_H

#include "digitale.h"

class Epub : public Digitale
{
public:
    Epub(int s, QObject *parent = nullptr);
    std::string descrizione() const override;
};

#endif // EPUB_H
