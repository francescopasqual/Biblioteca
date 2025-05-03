#include "item.h"

// Costruttore: inizializza i campi della classe base
Item::Item(string t, string cr, string g, int an, int c, int p, QObject *parent)
    : QObject(parent),
    titolo(t),
    creatore(cr),
    genere(g),
    anno(an),
    copie(c),
    prestiti(p)
{}

// Distruttore: dealloca i formati associati
Item::~Item() {
    for (Formato* formato : formati) {
        delete formato;
    }
}

// Getter per titolo
string Item::getTitolo() const {
    return titolo;
}

// Getter per anno
int Item::getAnno() const {
    return anno;
}

// Getter per copie disponibili
int Item::getCopie() const {
    return copie;
}

// Getter per prestiti attivi
int Item::getPrestiti() const {
    return prestiti;
}

// Verifica disponibilità
bool Item::isDisponibile() const {
    return (copie - prestiti) > 0;
}

// Getter per formati
std::vector<Formato*> Item::getFormati() const {
    return formati;
}

// Incrementa i prestiti se ci sono copie disponibili
bool Item::incrementaPrestiti() {
    if (isDisponibile()) {
        prestiti++;
        return true;
    }
    return false;
}

// Decrementa i prestiti se ci sono prestiti attivi
bool Item::decrementaPrestiti() {
    if (prestiti > 0) {
        prestiti--;
        return true;
    }
    return false;
}

// Metodo showInfo() base (da sovrascrivere nelle sottoclassi)
void Item::showInfo() const {
    cout << "Titolo: " << titolo << endl
         << getTipoCreatore() << ": " << creatore << endl
         << "Genere: " << genere << endl
         << "Anno: " << anno << endl
         << "Copie disponibili: " << (copie - prestiti) << endl;

    //Formati
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


// Aggiungiamo un metodo per aggiungere Formati a un Item
void Item::addFormato(Formato* formato) {
    if (formato) { // Controlla che il puntatore non sia nullo
        formati.push_back(formato);
    }
}


std::string Item::getCreatore() const {
    return creatore;
}

std::string Item::getGenere() const {
    return genere;
}
