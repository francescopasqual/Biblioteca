#ifndef FILM_H
#define FILM_H

#include "item.h"

class Film : public Item {

private:
    int durata;//in minuti
    std::string attore_principale;

public:
    Film(std::string t, std::string regista, std::string genere, int an, int c, int p, int d, std::string ap, QObject* parent = nullptr);
    std::string getTipoCreatore() const override;
    void showInfo() const override;
    int getDurata() const;
    std::string getAttore_principale() const;
};

#endif // FILM_H
