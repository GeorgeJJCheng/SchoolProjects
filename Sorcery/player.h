#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <random>
#include <memory>
#include "card.h"

class Player
{
    public:
        Player();
        Player(int pNum, std::string name, std::string decklist);
        virtual ~Player();

        //Card and hand functions
        void fillDeck();
        void shuffleDeck();
        void draw(int n);
        std::shared_ptr<Card> discard(int i);
        void startTurn();
        void setSeed(int s);

        //Get functions
        std::string getName();
        int getHP();
        int getCurMana();
        int getMaxMana();
        int getPNum();
        int getHandSize();
        std::shared_ptr<Card> getCard(int c);

        //Interaction functions
        void modHP(int n);
        bool spendMana(int n, bool testing);
        void mulligan(std::vector<int> indexes);
        bool getMull();
        void noMull();
        void printDeck();
        bool addCard(std::shared_ptr<Card>card);
        void builddeck();

    protected:
    private:
        bool canMull;
        std::mt19937 randEngine;
        std::uniform_int_distribution <int> randGen;
        int seed;
        std::vector <std::shared_ptr<Card>> hand;
        std::vector <std::shared_ptr<Card>> deck;
        int pNum;
        int maxHP;
        int hp; //Need maxHP/defaultHP value?
        int maxMana;
        int curMana;
        std::string decklist;
        std::string name;
};

#endif // PLAYER_H
