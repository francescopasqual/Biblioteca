#include "vinile.h"

Vinile::Vinile(string t, int an, int c, int pr, string p, string g, QObject *parent)
    : Item(t,an,c,pr,parent), performer(p), genere_musicale(g) {}

void Vinile::showInfo() const
{
    Item::showInfo();
    cout << "\n" << "Performer: " << performer << "\n" << "Genere musicale: " << genere_musicale << endl;
}

string Vinile::getPerformer() const { return performer; }

string Vinile::getGenereMusicale() const { return genere_musicale; }
