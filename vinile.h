#ifndef VINILE_H
#define VINILE_H

#include "item.h"
#include <string>
#include <QDebug>

class Vinile : public Item {
private:

    int numeroTracce;
    int durataTotale;

public:
    Vinile(string t, string performer, string genere, int an, int c, int p, int nt, int dt, QObject* parent = nullptr);
    string getTipoCreatore() const override;
    void showInfo() const override;


    int getNumeroTracce() const;
    int getDurataTotale() const;
};

#endif // VINILE_H
