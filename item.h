#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <string>
#include <vector>
#include "formato.h"
#include <iostream>

using std::string;
using std::cout; using std::endl;


class Item : public QObject {
    Q_OBJECT

protected:
    std::string titolo;
    std::string creatore;  // Autore/Regista/Performer
    std::string genere;    // Genere comune
    int anno;
    int copie;
    int prestiti;
    std::vector<Formato*> formati;

public:
    Item(std::string t, std::string cr, std::string g, int an, int c, int p, QObject* parent = nullptr);
    virtual ~Item();

    // Metodi virtuali puri per obbligare le sottoclassi a implementarli
    virtual std::string getTipoCreatore() const = 0;  // Es: "Autore", "Regista"
    virtual void showInfo() const;

    // Getter (implementati in Item.cpp)
    std::string getTitolo() const;
    std::string getCreatore() const;
    std::string getGenere() const;
    int getAnno() const;
    int getCopie() const;
    int getPrestiti() const;
    bool isDisponibile() const;
    std::vector<Formato*> getFormati() const;

    bool incrementaPrestiti();
    bool decrementaPrestiti();
    void addFormato(Formato *formato);
};

#endif // ITEM_H
