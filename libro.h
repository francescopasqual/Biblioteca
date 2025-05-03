#ifndef LIBRO_H
#define LIBRO_H

#include "item.h"

class Libro : public Item {
private:
    int pagine;

public:
    Libro(std::string t, std::string autore, std::string genere, int an, int c, int p, int pag, QObject* parent = nullptr);
    std::string getTipoCreatore() const override;
    void showInfo() const override;
    int getPagine() const;
};

#endif // LIBRO_H
