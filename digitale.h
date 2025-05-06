#ifndef DIGITALE_H
#define DIGITALE_H

#include "formato.h"

class Digitale : public Formato
{
    Q_OBJECT // Aggiungi Q_OBJECT

private:
    int sizeMB;

public:
    explicit Digitale(int s=0, QObject *parent = nullptr);
    virtual ~Digitale() = default;

    // Dichiara descrizione come pura virtuale qui per renderla astratta
    virtual std::string descrizione() const override = 0; // PURA VIRTUALE

    // Getter per sizeMB (necessario per Epub/Mp4)
    int getSizeMB() const;


};

#endif // DIGITALE_H
