#ifndef FILM_H
#define FILM_H

#include "item.h"

class Film : public Item {
private:
    unsigned int durata; // in minuti
    string attore_principale;

public:
    // Costruttore
    Film(const string &id, const string &t, const string &cr, unsigned int an, const string &g, unsigned int c,
         unsigned int p, unsigned int dur, const string &attore, QObject *parent = nullptr);

    //Distruttore
    ~Film() = default;

    //Per visitor
    void accept(ItemVisitor* visitor) override;

    // Override dei metodi virtuali
    void showInfo() const override;

    // Metodi specifici della classe Film
    unsigned int getDurata() const;
    string getAttore_principale() const;
};

#endif // FILM_H
