#include "biblioteca.h"
#include <algorithm>
#include <iostream>

// Costruttore
Biblioteca::Biblioteca(QObject *parent)
    : QObject{parent}
{
    catalogo = std::vector<Item*>();
}

// Distruttore
Biblioteca::~Biblioteca()
{
    for(Item* item : catalogo) {
        delete item;
    }
    catalogo.clear();
}

// Aggiunge un item al catalogo
void Biblioteca::addItem(Item *new_item)
{
    if (new_item) {
        catalogo.push_back(new_item);
        emit itemAdded(new_item);
    }
}

// Rimuove un item dal catalogo
void Biblioteca::removeItem(Item *item)
{
    auto it = std::remove(catalogo.begin(), catalogo.end(), item);
    if (it != catalogo.end()) {
        for (auto delete_it = it; delete_it != catalogo.end(); ++delete_it) {
            delete *delete_it;
        }
        catalogo.erase(it, catalogo.end());
        emit itemRemoved(item);
    } else {
        qWarning() << "Tentativo di rimuovere un item non presente nel catalogo.";
    }
}

// Restituisce il catalogo
std::vector<Item*> Biblioteca::getCatalogo() const
{
    return catalogo;
}

// Ricerca per titolo (generico)
std::vector<Item*> Biblioteca::searchByTitle(const string &titolo) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(item->getTitolo() == titolo) {
            result.push_back(item);
        }
    }
    return result;
}

// Ricerca per anno (generico)
std::vector<Item*> Biblioteca::searchByYear(unsigned int anno) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(item->getAnno() == anno) {
            result.push_back(item);
        }
    }
    return result;
}

// Ricerca per genere (generico)
std::vector<Item*> Biblioteca::searchByGenre(const string &genere) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(item->getGenere() == genere) {
            result.push_back(item);
        }
    }
    return result;
}

// Ricerca per creatore (generico)
std::vector<Item*> Biblioteca::searchByCreator(const string &creatore) const
{
    std::vector<Item*> result;
    for(Item* item : catalogo) {
        if(item->getCreatore() == creatore) {
            result.push_back(item);
        }
    }
    return result;
}



// Prestito di un item
bool Biblioteca::prestaItem(Item *item)
{
    auto it = std::find(catalogo.begin(), catalogo.end(), item);
    if (it == catalogo.end()) {
        qWarning() << "Tentativo di prestare un item non presente nel catalogo.";
        return false;
    }

    if ((*it)->incrementaPrestiti()) {
        emit itemStateChanged(*it);
        return true;
    }

    qDebug() << "L'item '" << QString::fromStdString((*it)->getTitolo()) << "' non è disponibile per il prestito.";
    return false;
}

// Restituzione di un item
bool Biblioteca::restituisciItem(Item *item)
{
    auto it = std::find(catalogo.begin(), catalogo.end(), item);
    if (it == catalogo.end()) {
        qWarning() << "Tentativo di restituire un item non presente nel catalogo.";
        return false;
    }

    if ((*it)->decrementaPrestiti()) {
        emit itemStateChanged(*it);
        return true;
    }

    qDebug() << "L'item '" << QString::fromStdString((*it)->getTitolo()) << "' non risulta in prestito.";
    return false;
}
