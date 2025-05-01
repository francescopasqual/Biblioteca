#ifndef LIBRO_H
#define LIBRO_H

#include "item.h"

class Libro : public Item
{

private:
    string autore;
    int pagine;
    string genere;

public:

    Libro(string t, int an, int c, int pr, string au, int p, string g, QObject *parent = nullptr);

    void showInfo() const override;

    //getter
    string getAutore() const;
    int getPagine() const;
    string getGenere() const;
};

#endif // LIBRO_H
