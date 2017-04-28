#ifndef RITUAL_H
#define RITUAL_H
#include <vector>
#include <string>
#include "card.h"
class Ritual: public Card
{
    std::string type;
    int cost;
    int ritcost;
    std::string name;
    std::string desc;
    std::string effect;
    int counter;
    std::string trigger;
    public:
        Ritual(int cost, std::string name, int ritcost, std::string desc, std::string effect, int counter, std::string trigger);
        ~Ritual();
        std::vector<std::string> print();
        std::string getEffect();
        std::string getName();
        std::string getType();
        std::string getTrigger();
        int getCost();
        int getRitCost();
        int getRitCounter();
        int getAbilityCost();
        void incCounter();
        void countDown();
         std::shared_ptr<Card> cardFactory();
};

#endif // RITUAL_H
