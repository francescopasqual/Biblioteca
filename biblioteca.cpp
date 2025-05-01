#include "biblioteca.h"

Biblioteca::Biblioteca(QObject *parent) : QObject(parent)
{
    // Inizializzazione del catalogo
    catalogo = std::vector<Item*>();
}

Biblioteca::~Biblioteca()
{
    for(auto i : catalogo) delete i;
}

void Biblioteca::addItem(Item *new_item)
{
    catalogo.push_back(new_item);
}

void Biblioteca::removeItem(Item *item)
{
    auto it = std::remove(catalogo.begin(), catalogo.end(), item);
    if(it != catalogo.end()) {
        delete *it; // Dealloca la memoria dell'oggetto
        catalogo.erase(it, catalogo.end());
    }
}

//ricerca per titolo generale
//ritorno un vettore nell'eventualità di item con lo stesso titolo
//(ad esempio diverse edizioni di un libro)
//idealmente non dovrebbero esserci duplicati nel catalogo
std::vector<Item*> Biblioteca::searchByTitle(string titolo) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(item->getTitolo() == titolo) {
            result.push_back(item);
        }
    }
    return result;
}


//ricerca per anno generale
std::vector<Item *> Biblioteca::searchByYear(int anno) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(item->getAnno() == anno) {
            result.push_back(item);
        }
    }
    return result;
}


//LIBRI
std::vector<Item *> Biblioteca::searchByGenre(string genere) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Libro* libro = dynamic_cast<Libro*>(item)) {
            if(libro->getGenere() == genere) {
                result.push_back(item);
            }
        }
    }

    return result;
}

std::vector<Item *> Biblioteca::searchByAuthor(string autore) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Libro* libro = dynamic_cast<Libro*>(item)) {
            if(libro->getAutore() == autore) {
                result.push_back(item);
            }
        }
    }

    return result;
}

//FILM
std::vector<Item *> Biblioteca::searchByRegista(string regista) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Film* film = dynamic_cast<Film*>(item)) {
            if(film->getRegista() == regista) {
                result.push_back(item);
            }
        }
    }

    return result;
}

std::vector<Item *> Biblioteca::searchByGenere(string genere) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Film* film = dynamic_cast<Film*>(item)) {
            if(film->getGenere() == genere) {
                result.push_back(item);
            }
        }
    }

    return result;
}

//VINILI
std::vector<Item *> Biblioteca::searchByPerformer(string performer) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Vinile* vinile = dynamic_cast<Vinile*>(item)) {
            if(vinile->getPerformer() == performer) {
                result.push_back(item);
            }
        }
    }

    return result;
}

std::vector<Item *> Biblioteca::searchByGenereMusicale(string genere) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Vinile* vinile = dynamic_cast<Vinile*>(item)) {
            if(vinile->getGenereMusicale() == genere) {
                result.push_back(item);
            }
        }
    }

    return result;
}

bool Biblioteca::prestaItem(Item *item)
{
    // Cerca l'item nel catalogo usando il puntatore
    auto it = std::find(catalogo.begin(), catalogo.end(), item);

    // Controlla se l'item è stato trovato nel catalogo
    if (it == catalogo.end()) {
        // Item non trovato nel catalogo gestito da questa Biblioteca
        std::cerr << "Errore: Tentativo di prestare un item non presente nel catalogo." << std::endl;
        return false;
    }

    // L'item è nel catalogo. Ora chiama il suo metodo per incrementare i prestiti.
    // Questo metodo in Item dovrebbe già controllare se è disponibile.
    if ((*it)->incrementaPrestiti()) {
        // Prestito registrato con successo all'interno dell'Item
        // Potresti emettere un segnale qui: emit itemStateChanged(*it);
        std::cout << "Prestito registrato con successo per l'item: " << (*it)->getTitolo() << std::endl;
        return true;
    } else {
        // Item non disponibile per il prestito
        std::cout << "L'item '" << (*it)->getTitolo() << "' non è disponibile per il prestito." << std::endl;
        return false;
    }

}

bool Biblioteca::restituisciItem(Item *item)
{
    // Cerca l'item nel catalogo usando il puntatore
    auto it = std::find(catalogo.begin(), catalogo.end(), item);

    // Controlla se l'item è stato trovato nel catalogo
    if (it == catalogo.end()) {
        // Item non trovato nel catalogo gestito da questa Biblioteca
        std::cerr << "Errore: Tentativo di restituire un item non presente nel catalogo." << std::endl;
        return false;
    }

    // L'item è nel catalogo. Ora chiama il suo metodo per decrementare i prestiti.
    // Questo metodo in Item dovrebbe già controllare se ci sono prestiti attivi da decrementare.
    if ((*it)->decrementaPrestiti()) {
        // Restituzione registrata con successo all'interno dell'Item
        // Potresti emettere un segnale qui: emit itemStateChanged(*it);
        std::cout << "Restituzione registrata con successo per l'item: " << (*it)->getTitolo() << std::endl;
        return true;
    } else {
        // L'item non risulta in prestito
        std::cout << "L'item '" << (*it)->getTitolo() << "' non risulta in prestito." << std::endl;
        return false;
    }

}
