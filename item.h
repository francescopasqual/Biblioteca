#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <string>
#include <iostream>
#include <vector>
#include "formato.h"
using std::string;
using std::cout; using std::endl;


class Item : public QObject
{
    Q_OBJECT

protected:

    string titolo;
    int anno;
    int copie;
    int prestiti;
    std::vector<Formato*> formati;


public:

    //costruttore
    Item(string t, int an, int c, int p, QObject *parent = nullptr);

    //distruttore
    virtual ~Item();

    //stampa info
    virtual void showInfo() const;

    //Getter
    string getTitolo() const;
    int getAnno() const;
    int getCopie() const;
    int getPrestiti() const;
    bool isDisponibile() const;
    std::vector<Formato*>getFormati() const;

    //per prestiti
    bool incrementaPrestiti();
    bool decrementaPrestiti();


};

#endif // ITEM_H
