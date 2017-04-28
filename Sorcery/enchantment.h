#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <vector>
#include <string>
#include "card.h"
class Enchantment: public Card{
    std::string type;
    int cost;
    std::string atk;
    std::string def;
    std::string name;
    std::string desc;
    std::string effect;
    bool modifyStats;
    bool activated;
    public:
        Enchantment(int cost, std::string name, std::string desc, std::string effect);
        Enchantment(int cost, std::string atk, std::string def, std::string name, std::string desc, std::string effect);
        ~Enchantment();
        std::vector<std::string> print();
        std::string getEffect();
        std::string getName();
        std::string getType();
        std::string getEnchAtk();
        std::string getEnchDef();
        int getCost();
        int getAbilityCost();
        void activate();
        bool getActivated();
        std::shared_ptr<Card> cardFactory();
};

#endif // ENCHANTMENT_H
