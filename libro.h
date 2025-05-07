#ifndef LIBRO_H
#define LIBRO_H

#include "item.h"

class Libro : public Item {

private:
    int pagine;

public:
    // Costruttore
    Libro(const string& id, const string& t, const string& cr, unsigned int an, const string& g, unsigned int c,
            unsigned int p, int pag, QObject* parent = nullptr);

    void showInfo() const override;

    // Metodi specifici della classe Libro
    int getPagine() const;
};

#endif // LIBRO_H
