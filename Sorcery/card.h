#ifndef CARD_H
#define CARD_H
#include "ascii_graphics.h"
#include <vector>
#include <memory>

class Card
{
    public:
        virtual ~Card();
        virtual std::vector<std::string> print();
        virtual std::string getEffect();
        virtual std::string getName();
        virtual std::string getType();
        virtual std::string getTrigger();
        virtual std::string getEnchAtk();
        virtual std::string getEnchDef();
        virtual int getDef();
        virtual int getAtk();
        virtual int getOrigDef();
        virtual int getOrigAtk();
        virtual int getCost();
        virtual bool getTarget();
        virtual int getAbilityCost();
        virtual int getRitCounter();
        virtual int getRitCost();
        virtual int getActions();
        virtual void modDef(int mod);
        virtual void setAtk(int atk);
        virtual void setDef(int def);
        virtual void countDown();
        virtual void setActions(int actions);
        virtual void decActions();
        virtual void incActions();
        virtual void incCounter();
        virtual int getMaxActions();
        virtual void incMaxActions();
        virtual int getNumEnch();
        virtual std::shared_ptr<Card> getEnch(int i);
        virtual std::shared_ptr<Card> cardFactory();
        virtual void activate();
        virtual bool getActivated();
        virtual void addEnch(std::shared_ptr<Card>enchantment);
        virtual void setAbilityCost(int a);
        virtual void removeEnch();
        virtual void restoreDefaults();
};

#endif // CARD_H
