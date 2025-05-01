#ifndef FILM_H
#define FILM_H

#include "item.h"

class Film : public Item
{
private:
    string regista;
    string genere;

public:
    Film(string t, int an, int c, int pr, string r, string g, QObject *parent = nullptr);
    void showInfo() const override;

    //getter
    string getRegista() const;
    string getGenere() const;
};

#endif // FILM_H
