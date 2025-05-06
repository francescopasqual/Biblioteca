#include "biblioteca.h"
#include <iostream> // Per std::cout, std::cerr, std::endl
#include <algorithm> // Per std::remove, std::find

// Assicurarsi che gli header specifici siano inclusi per dynamic_cast
#include "libro.h"
#include "film.h"
#include "vinile.h"


// Costruttore di default
Biblioteca::Biblioteca(QObject *parent)
    : QObject{parent}
{
    // Inizializza il catalogo come un vettore vuoto
    catalogo = std::vector<Item*>();
}

Biblioteca::~Biblioteca()
{
    // Dealloca tutti gli Item* nel catalogo
    for(Item* item : catalogo) { // Usare Item* item esplicita l'intento
        delete item; // Chiama il distruttore virtuale di Item, che a sua volta dealloca i formati
    }
    catalogo.clear(); // Opzionale, ma buona pratica dopo la deallocazione
}

void Biblioteca::addItem(Item *new_item)
{
    if (new_item) { // Controlla che il puntatore non sia nullo
        catalogo.push_back(new_item);
        // Potresti emettere un segnale qui: emit itemAdded(new_item);
    }
}

void Biblioteca::removeItem(Item *item)
{
    // Utilizza std::remove per spostare l'elemento da rimuovere alla fine del vettore
    // e ritorna un iteratore alla nuova fine logica del vettore.
    auto it = std::remove(catalogo.begin(), catalogo.end(), item);

    // Controlla se l'item è stato trovato (it sarà diverso da catalogo.end() se trovato)
    if(it != catalogo.end()) {
        // Dealloca la memoria degli oggetti nella porzione "rimossa" (dall'iteratore 'it' alla fine reale)
        // In questo caso, std::remove sposta solo l'item da rimuovere in fondo,
        // quindi la porzione da cancellare contiene solo l'item puntato da 'it'.
        for (auto delete_it = it; delete_it != catalogo.end(); ++delete_it) {
            delete *delete_it; // Dealloca l'oggetto
        }
        // Rimuove gli elementi dalla fine del vettore fisico
        catalogo.erase(it, catalogo.end());
        // Potresti emettere un segnale qui: emit itemRemoved(item);
    } else {
        // Opzionale: stampa un avviso se l'item non è stato trovato
        std::cerr << "Attenzione: Tentativo di rimuovere un item non presente nel catalogo." << std::endl;
    }
}

// Restituisce il catalogo (copia del vettore di puntatori)
std::vector<Item*> Biblioteca::getCatalogo() const
{
    // Restituisce una COPIA del vettore di puntatori.
    // Gli oggetti puntati non sono copiati.
    return catalogo;
}

// Funzioni di ricerca generali
std::vector<Item*> Biblioteca::searchByTitle(std::string titolo) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        // Confronto tra std::string e std::string (o QString e QString se cambi)
        if(item->getTitolo() == titolo) {
            result.push_back(item);
        }
    }
    return result;
}

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


// Funzioni di ricerca specifiche per tipo di Item
std::vector<Item *> Biblioteca::searchByGenre(std::string genere) const // Ricerca per genere nei Libri
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        // Prova a convertire il puntatore Item* a Libro*
        if(Libro* libro = dynamic_cast<Libro*>(item)) {
            // Se la conversione ha successo (è un Libro), controlla il genere
            if(libro->getGenere() == genere) {
                result.push_back(item); // Aggiungi il puntatore Item* al risultato
            }
        }
    }
    return result;
}

std::vector<Item *> Biblioteca::searchByAuthor(std::string autore) const // Ricerca per autore nei Libri
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        // Prova a convertire il puntatore Item* a Libro*
        if(Libro* libro = dynamic_cast<Libro*>(item)) {
            // Se la conversione ha successo, controlla il creatore (che per Libro è l'autore)
            if(libro->getCreatore() == autore) { // Usare getCreatore() che è public in Item
                result.push_back(item);
            }
        }
    }
    return result;
}

// FILM (stesse considerazioni per dynamic_cast e getCreatore)
std::vector<Item *> Biblioteca::searchByRegista(std::string regista) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Film* film = dynamic_cast<Film*>(item)) {
            if(film->getCreatore() == regista) { // Usare getCreatore()
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<Item *> Biblioteca::searchByGenere(std::string genere) const // Ricerca per genere nei Film
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

// VINILI
std::vector<Item *> Biblioteca::searchByPerformer(std::string performer) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Vinile* vinile = dynamic_cast<Vinile*>(item)) {
            if(vinile->getCreatore() == performer) {
                result.push_back(item);
            }
        }
    }
    return result;
}

//ricerca per genere
std::vector<Item *> Biblioteca::searchByGenereMusicale(std::string genere) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(Vinile* vinile = dynamic_cast<Vinile*>(item)) {
            if(vinile->getGenere() == genere) {
                result.push_back(item);
            }
        }
    }
    return result;
}


// FUNZIONI DI PRESTITO
bool Biblioteca::prestaItem(Item *item)
{
    // Cerca l'item nel catalogo usando il puntatore
    auto it = std::find(catalogo.begin(), catalogo.end(), item);

    // Controlla se l'item è stato trovato nel catalogo
    if (it == catalogo.end()) {
        // Item non trovato nel catalogo gestito da questa Biblioteca
        // Usare qWarning o qCritical per output Qt-style
        qWarning() << "Biblioteca::prestaItem: Tentativo di prestare un item non presente nel catalogo.";
        // Puoi anche usare std::cerr se preferisci, ma con Qt, qWarning/qDebug/qCritical sono comuni.
        return false;
    }

    // L'item è nel catalogo. Ora chiama il suo metodo per incrementare i prestiti.
    // Questo metodo in Item dovrebbe già controllare se è disponibile.
    if ((*it)->incrementaPrestiti()) {
        // Prestito registrato con successo all'interno dell'Item
        qDebug() << "Biblioteca::prestaItem: Prestito registrato con successo per l'item:" << QString::fromStdString((*it)->getTitolo());
        // Potresti emettere un segnale qui: emit itemStateChanged(*it);
        return true;
    } else {
        // Item non disponibile per il prestito
        qDebug() << "Biblioteca::prestaItem: L'item '" << QString::fromStdString((*it)->getTitolo()) << "' non è disponibile per il prestito.";
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
        qWarning() << "Biblioteca::restituisciItem: Tentativo di restituire un item non presente nel catalogo.";
        return false;
    }

    // L'item è nel catalogo. Ora chiama il suo metodo per decrementare i prestiti.
    // Questo metodo in Item dovrebbe già controllare se ci sono prestiti attivi da decrementare.
    if ((*it)->decrementaPrestiti()) {
        // Restituzione registrata con successo all'interno dell'Item
        qDebug() << "Biblioteca::restituisciItem: Restituzione registrata con successo per l'item:" << QString::fromStdString((*it)->getTitolo());
        // Potresti emettere un segnale qui: emit itemStateChanged(*it);
        return true;
    } else {
        // L'item non risulta in prestito
        qDebug() << "Biblioteca::restituisciItem: L'item '" << QString::fromStdString((*it)->getTitolo()) << "' non risulta in prestito.";
        return false;
    }
}

// La persistenza dei dati con JSON andrebbe implementata qui o in una classe dedicata
// che opera sulla Biblioteca.
