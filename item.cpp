#include "item.h"

//costruttore
Item::Item(string t, int an, int c, int p, QObject *parent)
    : QObject{parent}, titolo(t), anno(an), copie(c), prestiti(p) {}


//distruttore
Item::~Item()
{
    for(Formato* formato : formati) delete formato;
}

void Item::showInfo() const
{
    cout << "Titolo: " << titolo << "\n" << "Anno: " << anno << endl;
    if(copie-prestiti != 0) cout << "Copie disponibili: " << copie-prestiti << endl;
    else cout << "Al momento non ci sono copie disponibili" << endl;

    if(!(formati.empty())) {
        cout << "Formati disponibili: " << endl;
        for(const Formato* formato : formati){
            cout << "- " << formato->descrizione() << endl;
        }

    }else cout << "Nessun formato disponibile." << endl;

}

string Item::getTitolo() const {return titolo;}

int Item::getAnno() const {return anno;}

int Item::getCopie() const {return copie;}

int Item::getPrestiti() const {return prestiti;}

bool Item::isDisponibile() const {return (copie-prestiti) != 0;}

std::vector<Formato*> Item::getFormati() const
{
    std::vector<Formato*> result;
    for(auto formato : formati) result.push_back(formato);
    return result;
}

bool Item::incrementaPrestiti() {
    if(isDisponibile()) {
        prestiti++;
        return true;
    } else {
        cout << "Non ci sono copie disponibili per il prestito." << endl;
        return false;
    }
}

bool Item::decrementaPrestiti() {
    if(prestiti > 0) {
        prestiti--;
        return true;
    } else {
        cout << "Non ci sono prestiti attivi da restituire." << endl;
        return false;
    }
}

