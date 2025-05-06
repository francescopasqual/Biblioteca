#include "itemfactory.h"

Item* ItemFactory::createItem(
    ItemType type,
    const string& id,
    const string& titolo,
    const string& creatore,
    unsigned int anno,
    const string& genere,
    unsigned int copie,
    unsigned int prestiti,
    const ItemSpecificParams& specificParams,
    const std::vector<Formato*>& formati,
    QObject* parent)
{
    // Validazione dei parametri comuni
    if (id.empty()) throw std::invalid_argument("ID non può essere vuoto");
    if (titolo.empty()) throw std::invalid_argument("Titolo non può essere vuoto");
    if (creatore.empty()) throw std::invalid_argument("Creatore non può essere vuoto");
    if (genere.empty()) throw std::invalid_argument("Genere non può essere vuoto");
    if (anno == 0) throw std::invalid_argument("Anno non può essere zero");
    if (copie == 0) throw std::invalid_argument("Numero di copie non può essere zero");
    if (prestiti > copie) throw std::invalid_argument("Prestiti non possono superare il numero di copie");

    // Puntatore all'item che verrà creato
    Item* item = nullptr;

    // Creazione dell'item appropriato in base al tipo
    switch (type) {
    case ItemType::LIBRO:
        if (!specificParams.pagine.has_value()) {
            throw std::invalid_argument("Pagine richieste per creare un Libro");
        }
        item = new Libro(id, titolo, creatore, anno, genere, copie, prestiti,
                         specificParams.pagine.value(), parent);
        break;

    case ItemType::FILM:
        if (!specificParams.durata.has_value() || !specificParams.attore_principale.has_value()) {
            throw std::invalid_argument("Durata e attore principale richiesti per creare un Film");
        }
        item = new Film(id, titolo, creatore, anno, genere, copie, prestiti,
                        specificParams.durata.value(), specificParams.attore_principale.value(), parent);
        break;

    case ItemType::VINILE:
        if (!specificParams.numeroTracce.has_value() || !specificParams.durataTotale.has_value()) {
            throw std::invalid_argument("Numero tracce e durata totale richiesti per creare un Vinile");
        }
        item = new Vinile(id, titolo, creatore, anno, genere, copie, prestiti,
                          specificParams.numeroTracce.value(), specificParams.durataTotale.value(), parent);
        break;

    default:
        throw std::invalid_argument("Tipo di item non supportato");
    }

    // Aggiungiamo i formati all'item
    for (Formato* formato : formati) {
        if (formato) {
            item->addFormato(formato);
        }
    }

    return item;
}



