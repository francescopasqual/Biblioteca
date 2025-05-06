#include "item.h"

// Costruttore: inizializza i campi della classe base
Item::Item(const string &id, const string &t, const string &cr, unsigned int an, const string &g, unsigned int c, unsigned int p, QObject *parent)
    : QObject(parent), ID(id), titolo(t), creatore(cr), anno(an), genere(g), copie(c), prestiti(p)
{
    //vettore dei formati si inizializza vuoto di default

}

// Distruttore: dealloca i formati associati
Item::~Item() {
    for (Formato* formato : formati) {
        delete formato;
    }
}

// Metodo showInfo() base
void Item::showInfo() const {
    cout << "Titolo: " << titolo << endl
         << "Creatore: " << creatore << endl
         << "Genere: " << genere << endl
         << "Anno: " << anno << endl
         << "Copie disponibili: " << (copie - prestiti) << endl;

    // Formati
    if (formati.empty()) {
        std::cout << "  Nessun formato specificato." << std::endl;
    } else {
        // Itera sul vettore di formati e stampa la descrizione di ciascuno
        for (const Formato* formato : formati) {
            // Chiama il metodo virtuale descrizione() sul puntatore Formato*
            std::cout << "  - " << formato->descrizione() << std::endl;
        }
    }
    std::cout << "-------------------------" << std::endl; // Separatore di chiusura
}

// Getters
string Item::getID() const {return ID;}
string Item::getTitolo() const {return titolo;}
string Item::getCreatore() const {return creatore;}
string Item::getGenere() const {return genere;}
unsigned int Item::getAnno() const {return anno;}
unsigned int Item::getCopie() const {return copie;}
unsigned int Item::getPrestiti() const {return prestiti;}
std::vector<Formato *> Item::getFormati() const {return formati;}

void Item::addFormato(Formato *formato)
{
    formati.push_back(formato);
}

// Metodi per la gestione dei prestiti
bool Item::incrementaPrestiti() {
    if (isAvailable()) {
        prestiti++;
        return true;
    }
    return false;
}

bool Item::decrementaPrestiti() {
    if (prestiti > 0) {
        prestiti--;
        return true;
    }
    return false;
}

bool Item::isAvailable() const {
    return (copie > prestiti);
}
