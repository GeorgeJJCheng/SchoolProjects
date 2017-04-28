#ifndef CARDLIST_H
#define CARDLIST_H
#include <vector>
#include <memory>
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
class CardList{
    std::vector<std::shared_ptr<Card>> library;
    std::string filename;
    public:
        CardList(std::string filename);
        ~CardList();
        void LoadCards();
        std::shared_ptr<Card> getCard(std::string name);
};

#endif // CARDLIST_H
