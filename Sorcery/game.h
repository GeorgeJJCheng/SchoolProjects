#ifndef GAME_H
#define GAME_H
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "player.h"
#include "card.h"

class Game
{
    public:
        Game();
        Game(std::string deckP1, std::string deckP2, std::string initFile, bool testing, bool graphics);
        virtual ~Game();
        void init();
        bool gameLoop();
        //void endGame(std::shared_ptr <Player> winner);
        bool interpret(std::string cmd);
        void playCard(std::shared_ptr <Card> thisCard, int player, int target);
        void destroyCard(int c);
        void dispBoard();
        void dispCurHand();
        void describe(std::shared_ptr<Card> thisCard);
        void parallelPrint(std::vector<std::vector<std::string>> cards);
        //void returnCard(int c); //Returns a card from the grave to somewhere.

        //Trigger checks
        //Each trigger looks through all cards on both fields and activates appropriate effects.
        void triggerEffects(std::string trigger, int p, int t);

        //std::vector <std::string> getTemplate(std::shared_ptr<Card> thisCard);
        void attack(std::shared_ptr<Card> source, std::shared_ptr<Card> target);
        bool checkDeath(int p, int i);
        bool useEffect(std::shared_ptr<Card> thisCard, std::string effect, int owner, int target, bool isTrigger);

    protected:
    private:
        int turns;
        bool testing;
        bool deckbuilder;
        bool gameOver;
        std::ifstream scriptInit;
        //std::string cmd;
        std::string initFile;
        std::shared_ptr<Player> p1;
        std::string deck1;
        std::shared_ptr<Player> p2;
        std::string deck2;
        std::shared_ptr<Player> currentP;
        std::shared_ptr<Player> otherP;
        std::vector <std::shared_ptr<Card>> fieldP1;
        std::vector <std::shared_ptr<Card>> graveP1;
        std::shared_ptr<Card> ritualP1; //Potentially change to ritual instead of card type
        std::vector <std::shared_ptr<Card>> fieldP2;
        std::vector <std::shared_ptr<Card>> graveP2;
        std::shared_ptr<Card> ritualP2;
};

#endif // GAME_H
