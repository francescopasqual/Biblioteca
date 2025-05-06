#ifndef LIBRO_H
#define LIBRO_H

#include "item.h"

class Libro : public Item {
private:
    int pagine;

public:
    // Costruttore
    Libro(const string& id, const string& t, const string& autore, const string& genere, const string& an,
          unsigned int c, unsigned int p, const std::vector<Formato*>& formati, int pag, QObject* parent = nullptr);

    void showInfo() const override;

    // Metodi specifici della classe Libro
    int getPagine() const;
};

#endif // LIBRO_H
