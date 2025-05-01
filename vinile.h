#ifndef VINILE_H
#define VINILE_H

#include "item.h"

class Vinile : public Item
{
private:
    string performer;
    string genere_musicale;
public:
    Vinile(string t, int an, int c, int pr, string p, string g, QObject *parent = nullptr);
    void showInfo() const override;

    //getter
    string getPerformer() const;
    string getGenereMusicale() const;
};

#endif // VINILE_H
