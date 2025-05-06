#ifndef FILM_H
#define FILM_H

#include "item.h"

class Film : public Item {
private:
    int durata; // in minuti
    string attore_principale;

public:
    // Costruttore
    Film(const string& id, const string& t, const string& regista, const string& genere, const string& an,
         unsigned int c, unsigned int p, const std::vector<Formato*>& formati, int d, const string& ap, QObject* parent = nullptr);

    // Override dei metodi virtuali
    void showInfo() const override;

    // Metodi specifici della classe Film
    int getDurata() const;
    string getAttore_principale() const;
};

#endif // FILM_H
