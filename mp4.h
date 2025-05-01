#ifndef MP4_H
#define MP4_H

#include "digitale.h"

class Mp4 : public Digitale
{
public:
    Mp4(int s, QObject *parent = nullptr);
    std::string descrizione() const override;
};

#endif // MP4_H
