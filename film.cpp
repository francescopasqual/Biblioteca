#include "film.h"

Film::Film(string t, int an, int c, int pr, string r, string g, QObject *parent)
    : Item(t, an, c, pr, parent), regista(r), genere(g) {}

void Film::showInfo() const
{
    Item::showInfo();
    cout << "\n" << "Regista: " << regista << "\n" << "Genere: " << genere << endl;
}

string Film::getRegista() const { return regista; }

string Film::getGenere() const {return genere;}
