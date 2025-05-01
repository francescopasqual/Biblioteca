#include "libro.h"

Libro::Libro(string t, int an, int c, int pr, string au, int p, string g, QObject *parent)
    : Item(t,an,c,pr,parent), autore(au), pagine(p), genere(g) {}

void Libro::showInfo() const
{
    Item::showInfo();
    cout << "\n" << "Autore: " << autore << "\n" << "Numero di pagine: " << pagine
         << "\n" << "Genere: " << genere << endl;
}

string Libro::getAutore() const {return autore;}

int Libro::getPagine() const {return pagine;}

string Libro::getGenere() const {return genere;}
