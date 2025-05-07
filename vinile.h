#ifndef VINILE_H
#define VINILE_H

#include "item.h"
#include <string>
#include <QDebug>

class Vinile : public Item {
private:
    unsigned int numeroTracce;
    unsigned int durataTotale;

public:
    // Costruttore
    Vinile(const string &id, const string &t, const string &cr, unsigned int an, const string &g, unsigned int c,
           unsigned int p, unsigned int numTracce, unsigned int durTotale, QObject *parent = nullptr);

    //Distruttore
    ~Vinile() = default;

    // Visitor
    void accept(ItemVisitor* visitor) override;


    void showInfo() const override;

    // Metodi specifici della classe Vinile
    unsigned int getNumeroTracce() const;
    unsigned int getDurataTotale() const;
};

#endif // VINILE_H
