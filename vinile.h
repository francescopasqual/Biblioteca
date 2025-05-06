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
    // Costruttore
    Vinile(const string& id, const string& t, const string& performer, const string& genere, const string& an,
           unsigned int c, unsigned int p, const std::vector<Formato*>& formati, int nt, int dt, QObject* parent = nullptr);

    void showInfo() const override;

    // Metodi specifici della classe Vinile
    int getNumeroTracce() const;
    int getDurataTotale() const;
};

#endif // VINILE_H
