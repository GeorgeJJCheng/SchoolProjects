#ifndef MINION_H
#define MINION_H
#include <vector>
#include <memory>
#include "enchantment.h"
#include "ascii_graphics.h"
#include "card.h"
class Minion: public Card
{
    std::string type;
    int cost;
    std::string name;
    std::string desc;
    std::string effect;
    int actions;
    int maxActions;
    int def;
    int atk;
    int origdef;
    int origatk;
    int origeffcost;
    int origcost;
    int effCost;
    std::string origeffect;
    std::vector<std::shared_ptr<Card>> modifiers;
    std::string trigger;
    bool hasEffect;
    bool hasEffCost;
    bool targeted;

    public:
        Minion(int cost, std::string name, std::string desc, std::string effect, int def, int atk, std::string trigger);
        Minion(int cost, std::string name, std::string desc, std::string effect, int def, int atk, int effCost, bool targeted);
        Minion(int cost, std::string name, int def, int atk,std::string desc);
        Minion(const Minion &other);
        ~Minion();
        std::vector<std::string> print();
        void setAtk(int atk);
        void setDef(int def);
        void modDef(int mod);
        int getActions();
        int getAbilityCost();
        int getAtk();
        int getDef();
        int getOrigAtk();
        int getOrigDef();
        int getCost();
        bool getTarget();
        std::string getEffect();
        std::string getTrigger();
        std::string getName();
        std::string getType();
        void applyMods();
        void incActions();
        void decActions();
        int getNumEnch();
        void addEnch(std::shared_ptr<Card>enchantment);
        void removeEnch();
        std::shared_ptr<Card> getEnch(int i);
        std::shared_ptr<Card> cardFactory();
        int getMaxActions();
        void setActions(int a);
        void incMaxActions();
        void setAbilityCost(int a);
        void restoreDefaults();
};

#endif // MINION_H
