#ifndef SPELL_H
#define SPELL_H
#include <vector>
#include <string>
#include "card.h"
class Spell: public Card{
    std::string type;
    int cost;
    std::string name;
    std::string desc;
    std::string effect;
    bool targeted;
    public:
        Spell(int cost, std::string name, std::string desc, std::string effect, bool targeted);
        ~Spell();
        std::vector<std::string> print();
        std::string getEffect();
        std::string getName();
        std::string getType();
        int getCost();
        int getAbilityCost();
        std::shared_ptr<Card> cardFactory();
};

#endif // SPELL_H
