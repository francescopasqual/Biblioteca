#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"
#include "libro.h"
#include "film.h"
#include "vinile.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>


// Enum per identificare il tipo di Item
enum class ItemType {
    LIBRO,
    FILM,
    VINILE
};

// Struttura per i parametri opzionali specifici
struct ItemSpecificParams {
    // Parametri per Libro
    std::optional<int> pagine;

    // Parametri per Film
    std::optional<unsigned int> durata;
    std::optional<string> attore_principale;

    // Parametri per Vinile
    std::optional<unsigned int> numeroTracce;
    std::optional<unsigned int> durataTotale;
};


//Si occupa di generare ogni tipo di Item, compresi i suoi formati
class ItemFactory {

public:

    // Factory method che crea l'item appropriato basandosi sul tipo
    static Item* createItem(
        ItemType type,
        const string& id,
        const string& titolo,
        const string& creatore,
        unsigned int anno = 0,
        const string& genere = "",
        unsigned int copie = 0,
        unsigned int prestiti = 0,
        const ItemSpecificParams& specificParams = ItemSpecificParams(),
        const std::vector<Formato*>&  formati = {},
        QObject* parent = nullptr
        );

};

#endif // ITEMFACTORY_H
