#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "game.h"
#include "ascii_graphics.h"
#include "minion.h"
#include <ctime>
using namespace std;

Game::Game()
{
    //ctor
}

Game::Game(string deckP1, string deckP2, string initFile, bool testing, bool deckbuilder): testing(testing), deckbuilder(deckbuilder), gameOver(false), initFile(initFile), deck1(deckP1) , deck2(deckP2)
{

}

Game::~Game()
{
    /* With shared_ptr, may not need to delete.
    delete p1;
    delete p2;
    delete currentP;
    */
}

void Game::init()
{
    if(initFile != "default")
        scriptInit.open(initFile);
    string pName;
    cout << "Player 1, enter your name." << endl;
    if(initFile != "default" && !scriptInit.eof())
        scriptInit >> pName;
    else
        cin >> pName;
    p1 = make_shared<Player>(1, pName, deck1);
    if(deckbuilder)
        p1->builddeck();
    cout << "Player 2, enter your name." << endl;
    if(initFile != "default" && !scriptInit.eof())
        scriptInit >> pName;
    else
        cin >> pName;
    p2 = make_shared<Player>(2, pName, deck2);
    if(deckbuilder)
        p2->builddeck();
    currentP = p1;
    otherP = p2;
    ritualP1 = nullptr;
    ritualP2 = nullptr;
    p1->fillDeck();
    p2->fillDeck();
    if(!testing)
    {
        p1->shuffleDeck();
        p2->shuffleDeck();
    }
    p1->draw(4);
    p2->draw(5);

    turns = 0;
    while(gameLoop())
    {
        //idk, filler?
    }
    //endGame();
}

bool Game::gameLoop()
{
    currentP->startTurn(); //Player gains 1 mana and draws.
    if(currentP->getHandSize() == 11) //Hand size is 10, if overdraw, discard straight to grave.
    {
        if(currentP->getPNum() == 1)
            graveP1.push_back(currentP->discard(10));
        else
            graveP2.push_back(currentP->discard(10));
    }
    triggerEffects("startturn", 0, 0);
    dispBoard();
    string cmd = "start";
    while(interpret(cmd))
    {
        if(gameOver)
            return false;
        //dispBoard();
        cout << "Player " << currentP->getPNum() << ", " << currentP->getName() << "'s turn. Command?" << endl;
        if(turns/2 == 0 && currentP->getMull())
            cout << "You may mulligan any number of cards from your hand. This can only be done once. Syntax is mulligan indexes of cards in your hand, separated by spaces." << endl;
        if(initFile != "default")
        {
            if(scriptInit.eof())
            {
                initFile = "default";
                cin >> cmd;
            }
            else
                scriptInit >> cmd;
        }
        else
            cin >> cmd;
        if (cin.eof())
            cmd = "quit";
        if(cmd == "quit")
        {
             //end the game with no winner
             cout << "Game ended. No winner!" << endl;
             return false;
        }
    }
    triggerEffects("endturn", 0, 0);
    if(currentP->getPNum() == 1)
    {
        currentP = p2;
        otherP = p1;
    }
    else
    {
        currentP = p1;
        otherP = p2;
    }
    turns++;
    return true;
}


bool Game::interpret(string cmd) //Some incomplete functions within
{
    if(cmd == "end") //WORKING
        return false;
    else if (cmd == "help") //WORKING
    {
        cout << "Commands:" << endl;
        cout << "help -- Display this message." << endl;
        cout << "end -- End the current player's turn." << endl;
        cout << "quit -- End the game." << endl;
        cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
        cout << "attack minion -- Orders minion to directly attack the opponent." << endl;
        cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
        cout << "use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
        cout << "inspect minion -- View a minion's card and all enchantments on that minion." << endl;
        cout << "hand -- Describe all cards in your hand." << endl;
        cout << "board -- Describe all cards on the board." << endl;
        cout << "mulligan [indexes of cards] -- Return cards with specified index from the hand to the deck, then draw that many cards." << endl;
    }
    else if (cmd == "draw") //WORKING
    {
        if(testing)//Only available in testing mode, initialized by a command line argument
            currentP->draw(1);
        else
            cout << "draw is a testing-mode-only command." << endl;
        dispBoard();
    }
    else if (cmd == "discard") //WORKING
    {
        if(testing)
        {
            //Testing mode only
            int i;
            if(initFile == "default")
                cin >> i;
            else
                scriptInit >> i;
            currentP->discard(i-1);
        }
        else
            cout << "discard is a testing-mode-only command." << endl;
        dispBoard();
    }
    else if (cmd == "shuffle")
    {
        if(testing)
            currentP->shuffleDeck();
        else
            cout << "shuffle is a testing-mode-only command." << endl;
    }
    else if (cmd == "mulligan")
    {
        string s;
        getline(cin, s);
        if(testing || (turns/2 == 0 && currentP->getMull()))
        {
            vector<int> toMull;
            for(int i = 1; i < s.length(); i+=2)
                toMull.push_back(s[i]-'1');
            currentP->mulligan(toMull);
            dispBoard();
        }
        else
            cout << "Can't mulligan anymore!" << endl;
    }
    else if (cmd == "decklist")
    {
        if(testing)
            currentP->printDeck();
        else
            cout << "decklist is a testing-mode-only command." << endl;
    }
    else if (cmd == "attack") //WORKING
    {
        //Can take either one argument or two.
        int source;
        int target;
        string s;
        if(initFile == "default")
            getline(cin, s);
        else
            getline(scriptInit, s);
        source = s[1]-'0';
        if((currentP->getPNum() == 1 && source <= fieldP1.size()) || (currentP->getPNum() == 2 && source <= fieldP2.size()))
        {
            if(s.length() >= 4)
            {
                target = s[3]-'0';
                if(currentP->getPNum() == 1 && target <= fieldP2.size() && target > 0) //currently allows for target = 0, ISSUE
                {
                    if(fieldP1[source-1]->getActions() > 0)
                    {
                        cout << fieldP1[source-1]->getName() << "'s # of actions:" << fieldP1[source-1]-> getActions() << endl;
                        attack(fieldP1[source-1], fieldP2[target-1]);
                        checkDeath(1, source-1);
                        checkDeath(2, target-1);
                    }
                    else
                        cout << "This minion is out of actions!" << endl;
                }
                else if(currentP->getPNum() == 2 && target <= fieldP1.size() && target > 0)
                {
                    if(fieldP2[source-1]->getActions() > 0)
                    {
                        cout << fieldP2[source-1]->getName() << "'s # of actions:" << fieldP2[source-1]-> getActions() << endl;
                        attack(fieldP2[source-1], fieldP1[target-1]);
                        checkDeath(2, source-1);
                        checkDeath(1, target-1);
                    }
                    else
                        cout << "This minion is out of actions!" << endl;
                }
                else
                    cout << "Enemy #" << target << " is not a valid target!" << endl;
            }
            else
            {
                //cin.clear();
                if(currentP->getPNum() == 1)
                    if(fieldP1[source-1]->getActions() > 0)
                        attack(fieldP1[source-1], nullptr);
                    else
                        cout << "This minion is out of actions!" << endl;
                else
                    if(fieldP2[source-1]->getActions() > 0)
                        attack(fieldP2[source-1], nullptr);
                    else
                        cout << "This minion is out of actions!" << endl;
                if(otherP->getHP() <= 0)
                {
                    cout << currentP->getName() << " has won!" << endl;
                    gameOver = true;
                }
            }
            dispBoard();
        }
        else
            cout << "Minion #" << source << " is not a valid attacker!" << endl;
    }
    else if (cmd == "play") //WORKING
    {
        //Can take either one argument or three.
        int card;
        int p = 0;
        int t = 0;
        int fieldsize = currentP->getPNum() == 1 ? fieldP1.size() : fieldP2.size();
        if(initFile == "default")
            cin >> card;
        else
            scriptInit >> card;
        if(card < currentP->getHandSize()+1 && fieldsize <= 5 && currentP->spendMana(currentP->getCard(card-1)->getCost(), testing)) //Issue on fieldsize
        {
            if(currentP->getCard(card-1)->getType().substr(0, 6) == "Minion" || currentP->getCard(card-1)->getType().substr(0, 6) == "Ritual")
            {
                playCard(currentP->discard(card-1), p, t);
                if(currentP->getCard(card-1)->getType().substr(0, 6) == "Minion")
                {
                    if(currentP->getPNum() == 1)
                        triggerEffects("minenter", currentP->getPNum(), fieldP1.size());
                    else
                        triggerEffects("minenter", currentP->getPNum(), fieldP2.size());
                }
            }
            else
            {
                if (currentP->getCard(card-1)->getType() == "SpellT"){
                    if(initFile == "default")
                        cin >> p;
                    else
                        scriptInit >> p;
                    if(initFile == "default")
                        cin >> t;
                    else
                        scriptInit >> t;
                    string effect = currentP->getCard(card-1)->getEffect();
                    if(useEffect(currentP->getCard(card-1),effect,p,t,false)){
                        currentP->discard(card-1);
                    }else{
                        cout << "Card: " << currentP->getCard(card-1)->getName() << " cannot be played" << endl;
                    }
                }else if(currentP->getCard(card-1)->getType() == "Spell"){
                    string effect = currentP->getCard(card-1)->getEffect();
                    if(useEffect(currentP->getCard(card-1),effect,0,0,false)){
                        currentP->discard(card-1);
                    }else{
                        cout << "Card: " << currentP->getCard(card-1)->getName() << " cannot be played" << endl;
                    }
                }
                else{
                    if(initFile == "default")
                        cin >> p;
                    else
                        scriptInit >> p;
                    if(initFile == "default")
                        cin >> t;
                    else
                        scriptInit >> t;
                    if(p == 1)
                    {
                        if(useEffect(currentP->getCard(card-1),currentP->getCard(card-1)->getEffect(), p, t, true)){
                            fieldP1[t-1]->addEnch(currentP->discard(card-1));
                        }else{
                            cout << "Card: " << currentP->getCard(card-1)->getName() << " cannot be played" << endl;
                        }
                    }
                    else
                    {

                        if(useEffect(currentP->getCard(card-1), currentP->getCard(card-1)->getEffect(), p, t, true)){
                            fieldP2[t-1]->addEnch(currentP->discard(card-1));
                        }else{
                            cout << "Card: " << currentP->getCard(card-1)->getName() << " cannot be played" << endl;
                        }
                    }
                }
                //Spell or enchantment, with target.
            }
            dispBoard();
        }
        else
            cout << "You can't play that card!" << endl;
    }
    else if (cmd == "use") //WORKING
    {
        //Can take either one argument or three.
        int card;
        int p;
        int t;
        if(initFile == "default")
            cin >> card;
        else
            scriptInit >> card;
        bool silenced = false;
        if (currentP->getPNum() == 1){
            for (int i = 0; i < fieldP1[card-1]->getNumEnch(); i++){
                if(fieldP1[card-1]->getEnch(i)->getName() == "Silence"){
                    cout << "This card is silenced." << endl;
                    silenced = true;
                }
            }
        }else{
            for (int i = 0; i < fieldP2[card-1]->getNumEnch(); i++){
                if(fieldP2[card-1]->getEnch(i)->getName() == "Silence"){
                    cout << "This card is silenced." << endl;
                    silenced = true;
                }
            }
        }
       	bool hasAbility = false;
        if (currentP-> getPNum() == 1 && fieldP1[card-1]->getType() == "MinionAA" && card <= fieldP1.size())
            hasAbility = true;
        else if(currentP-> getPNum() == 2 && fieldP2[card-1]->getType() == "MinionAA" && card <= fieldP2.size())
            hasAbility = true;
        if(currentP->getPNum() == 1 && card <= fieldP1.size() && currentP->getCurMana() >= fieldP1[card-1]->getAbilityCost() && hasAbility && !silenced)
        {
            //cout << fieldP1[card-1]->getName() << "'s actions are: " << fieldP1[card-1]->getActions() << endl;
            if(fieldP1[card-1]->getActions() > 0)
            {
                //cout << "Card has ability" << endl;
                string effect = fieldP1[card-1]->getEffect();
                if(fieldP1[card-1]->getTarget()) //If card has a targeted ability
                {
                    if(initFile == "default")
                        cin >> p;
                    else
                        scriptInit >> p;
                    if(initFile == "default")
                        cin >> t;
                    else
                        scriptInit >> t;
                    //activate the effect on p's t
                    useEffect(fieldP1[card-1], effect, p, t, false);
                }
                else
                    useEffect(fieldP1[card-1], effect, 0, 0, false);
                dispBoard();
            }
            else
                cout << "This minion is out of actions!" << endl;
        }
        else if(currentP->getPNum() == 2 && card <= fieldP2.size() && currentP->getCurMana() >= fieldP2[card-1]->getAbilityCost() && hasAbility && !silenced)
        {
            cout << fieldP2[card-1]->getName() << "'s actions are: " << fieldP2[card-1]->getActions() << endl;
            if(fieldP2[card-1]->getActions() > 0)
            {
                string effect = fieldP2[card-1]->getEffect();
                if(fieldP2[card-1]->getTarget()) //If card has a targeted ability
                {
                    if(initFile == "default")
                        cin >> p;
                    else
                        scriptInit >> p;
                    if(initFile == "default")
                        cin >> t;
                    else
                        scriptInit >> t;
                    //activate the effect on p's t
                    useEffect(fieldP2[card-1], effect, p, t, false);
                }
                else
                    useEffect(fieldP2[card-1], effect, 0, 0, false);
                dispBoard();
            }
            else
                cout << "This minion is out of actions!" << endl;
        }
        else
            cout << "Can't use that card's ability!" << endl;
    }
    else if (cmd == "describe") //WORKING
    {
        int i;
        if(initFile == "default")
            cin >> i;
        else
            scriptInit >> i;
        if(currentP->getPNum() == 1)
            if (i <= fieldP1.size()){
                describe(fieldP1[i-1]);
            }else{
                cout << "Minion " << i << " does not exist on the field." << endl;
            }
        else
            if (i <= fieldP2.size()){
                describe(fieldP2[i-1]);
            }else{
                cout << "Minion " << i << " does not exist on the field." << endl;
            }
    }
    else if (cmd == "inspect")
    {
        int i;
        if(initFile == "default")
            cin >> i;
        else
            scriptInit >> i;
        if(i <= currentP->getHandSize())
            describe(currentP->getCard(i-1));
        else
            cout << "There is no card #" << i << " in your hand!" << endl;
    }
    else if (cmd == "hand") //WORKING
    {
        dispCurHand();
    }
    else if (cmd == "board") //WORKING
    {
        dispBoard();
    }
    else if (cmd == "start") //same
    {
        return true;
        //empty
    }
    else //WORKING
    {
        cout << "Invalid command. Enter [help] to see a list of valid commands." << endl;
    }
    currentP->noMull();
    return true;
}

void Game::playCard(shared_ptr<Card> thisCard, int player, int target) //WORKING
{
    if(player == 1 || player == 2)
    {
        useEffect(thisCard, thisCard->getEffect(), player, target, false);
    }
    else
    {
        if(currentP->getPNum() == 1)
        {
            //check if it's a ritual...
            if(thisCard->getType().substr(0, 6) == "Ritual")
                ritualP1 = thisCard;
            else if(thisCard->getType().substr(0, 6) == "Minion")
                fieldP1.push_back(thisCard);
        }
        else if(currentP->getPNum() == 2)
        {
            if(thisCard->getType().substr(0, 6) == "Ritual")
                ritualP2 = thisCard;
            else if(thisCard->getType().substr(0, 6) == "Minion")
                fieldP2.push_back(thisCard);
            //see above
        }
        else
            cout << "Not enough mana!" << endl;
    }
}

void Game::dispBoard() //TO DO: IMPLEMENT GRAPHICS OPTION
{
    //Displays differently depending on current player
    vector<vector<string>> p2Backline;
    if(ritualP2)
        p2Backline.push_back(ritualP2->print());
    else
        p2Backline.push_back(CARD_TEMPLATE_BORDER);
    p2Backline.push_back(CARD_TEMPLATE_BORDER);
    p2Backline.push_back(display_player_card(p2->getPNum(), p2->getName(), p2->getHP(), p2->getCurMana()));
    p2Backline.push_back(CARD_TEMPLATE_BORDER);
    if(graveP2.size() > 0)
        p2Backline.push_back(graveP2.back()->print());
    else
        p2Backline.push_back(CARD_TEMPLATE_BORDER);

    vector<vector<string>> p2FieldOut;
    for(int i = 0; i < fieldP2.size(); i++)
        p2FieldOut.push_back(fieldP2[i]->print());
    for(int i = 0; i < 5 - fieldP2.size(); i++)
        p2FieldOut.push_back(CARD_TEMPLATE_BORDER);

    vector<vector<string>> p1Backline;
    if(ritualP1)
        p1Backline.push_back(ritualP1->print());
    else
        p1Backline.push_back(CARD_TEMPLATE_BORDER);
    p1Backline.push_back(CARD_TEMPLATE_BORDER);
    p1Backline.push_back(display_player_card(p1->getPNum(), p1->getName(), p1->getHP(), p1->getCurMana()));
    p1Backline.push_back(CARD_TEMPLATE_BORDER);
    if(graveP1.size() > 0)
        p1Backline.push_back(graveP1.back()->print());
    else
        p1Backline.push_back(CARD_TEMPLATE_BORDER);

    vector<vector<string>> p1FieldOut;
    for(int i = 0; i < fieldP1.size(); i++)
        p1FieldOut.push_back(fieldP1[i]->print());
    for(int i = 0; i < 5 - fieldP1.size(); i++)
        p1FieldOut.push_back(CARD_TEMPLATE_BORDER);

    vector<string> centrePiece = CENTRE_GRAPHIC;

    if(currentP->getPNum() == 1)
    {
        parallelPrint(p2Backline);
        parallelPrint(p2FieldOut);
        for(int i = 0; i < centrePiece.size(); i++)
        {
            cout << centrePiece[i] << endl;
        }
        parallelPrint(p1FieldOut);
        parallelPrint(p1Backline);
    }
    else
    {
        parallelPrint(p1Backline);
        parallelPrint(p1FieldOut);
        for(int i = 0; i < centrePiece.size(); i++)
        {
            cout << centrePiece[i] << endl;
        }
        parallelPrint(p2FieldOut);
        parallelPrint(p2Backline);
    }
    dispCurHand();
}

void Game::dispCurHand() //TO DO: IMPLEMENT GRAPHICS OPTION
{
    //Get and display current player's hand
    cout << endl << "[ Hand ]" << endl << endl;
    vector<vector<string>> pHand;
    if(currentP->getHandSize() > 5) //Hand limit is now 10 lol
    {
        vector<vector<string>> pHand2;
        for(int a = 0; a < currentP->getHandSize()/5; a++)
        {
            for(int i = 0; i < 5; i++)
                pHand.push_back(currentP->getCard(i+a*5)->print());
            parallelPrint(pHand);
            pHand.clear();
        }
        for(int i = 0; i < currentP->getHandSize()%5; i++)
            pHand2.push_back(currentP->getCard(i+5)->print());
        parallelPrint(pHand2);
    }
    else
    {
        //cout << "The number of cards in hand atm is: " << currentP->getHandSize() << "This is player: " << currentP->getPNum() << endl;
        for(int i = 0; i < currentP->getHandSize(); i++)
            pHand.push_back(currentP->getCard(i)->print());
        parallelPrint(pHand);
    }
}

void Game::describe(shared_ptr<Card> thisCard) //GRAPHICS??
{
    vector<vector<string>> toPrint;
    toPrint.push_back(thisCard->print()); //Using card's print() instead of get_template
    parallelPrint(toPrint);
    if(thisCard->getType().substr(0,6) == "Minion" && thisCard->getNumEnch() > 0)
    {
        int e = thisCard->getNumEnch();
        for(int i = 0; i < e/5; i++)
        {
            vector<vector<string>> enchRow;
            for(int j = 0; j < 5; j++)
                enchRow.push_back(thisCard->getEnch(j+i*5)->print());
            parallelPrint(enchRow);
        }
        vector<vector<string>> lastRow;
        for(int i = 0; i < e%5; i++)
            lastRow.push_back(thisCard->getEnch(i+e-e%5)->print());
        parallelPrint(lastRow);
    }
}

void Game::parallelPrint(vector<vector<string>> cards) //WORKING, no need for graphics
{
    if(cards.size() > 0)
    {
        for(int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++)
        {
            for(int j = 0; j < cards.size(); j++)
            {
                cout << cards[j][i];
            }
            cout << endl;
        }
    }
}

void Game::triggerEffects(string trigger, int p, int t) //DONE, UNTESTED
{
    if(currentP->getPNum() == 1 || trigger == "minenter" || trigger == "minleave")
    {
        for(int i = 0; i < fieldP1.size(); i++)
        {
            if(fieldP1[i]->getActions() < fieldP1[i]->getMaxActions() && trigger == "startturn") //TO DO: Enchants
                 fieldP1[i]->setActions(fieldP1[i]->getMaxActions());
            if(fieldP1[i]->getTrigger() == trigger){
                if(p != currentP->getPNum() || trigger != "minenter" || t != i)
                {
                    if(trigger == "minleave"){
                        useEffect(fieldP1[i], fieldP1[i]->getEffect(), 1, i+1, true); //Currently only targets itself.
                    }
                    else{
                        useEffect(fieldP1[i], fieldP1[i]->getEffect(), p, t, true);
                    }
                }
            }
        }
        if(ritualP1)
        {
            if(ritualP1->getTrigger() == trigger){
               if(useEffect(ritualP1, ritualP1->getEffect(), p, t, false)){
                    ritualP1->countDown();
                    if(ritualP1->getRitCounter() == 0){
                        ritualP1 = nullptr;
                    }
               }
            }
        }
    }
    if(currentP->getPNum() == 2 || trigger == "minenter" || trigger == "minleave")
    {
        for(int i = 0; i < fieldP2.size(); i++)
        {
            if(fieldP2[i]->getActions() < fieldP2[i]->getMaxActions() && trigger == "startturn")
                 fieldP2[i]->setActions(fieldP2[i]->getMaxActions());
            if(fieldP2[i]->getTrigger() == trigger){
                if(p != currentP->getPNum() || trigger != "minenter" || t != i)
                {
                    if(trigger == "minleave"){
                        useEffect(fieldP2[i], fieldP2[i]->getEffect(), 2, i+1, true);
                    }
                    else{
                        useEffect(fieldP2[i], fieldP2[i]->getEffect(), p, t, true);
                    }
                }
            }
        }
        if(ritualP2)
        {
            if(ritualP2->getTrigger() == trigger){
                if(useEffect(ritualP2, ritualP2->getEffect(), p, t, false)){
                    ritualP2->countDown();
                    if(ritualP2->getRitCounter() == 0){
                        ritualP2 = nullptr;
                    }
                }
            }
        }
    }
}

void Game::attack(shared_ptr<Card> source, shared_ptr<Card> target) //WORKING
{
    if(!target)
        otherP->modHP(source->getAtk() * -1);
    else
    {
        //Attack an enemy minion
        target->modDef(source->getAtk() * -1);
        source->modDef(target->getAtk() * -1);
    }
    source->decActions();
}

bool Game::checkDeath(int p, int i) //WORKING
{
    if(p == 1)
    {
        if(fieldP1[i]->getDef() <= 0)
        {
            graveP1.push_back(fieldP1[i]);
            fieldP1.erase(fieldP1.begin()+i);
            triggerEffects("minleave", p, i);
            return true;
        }
    }
    else
    {
        if(fieldP2[i]->getDef() <= 0)
        {
            graveP2.push_back(fieldP2[i]);
            fieldP2.erase(fieldP2.begin()+i);
            triggerEffects("minleave", p, i);
            return true;
        }
    }
    return false;
}

bool Game::useEffect(shared_ptr<Card> thisCard, string effect, int owner, int target, bool isTrigger) //Triggers will not decrease actions.
{
    /*cout << "Card name: " << thisCard->getName() << endl;
    cout << "Ability Cost: " << thisCard->getAbilityCost() << endl;
    cout << "Effect String: " << thisCard->getEffect() << endl;
    cout << "Player: " << currentP->getPNum() << "'s current mana is: "<< currentP->getCurMana() <<  endl;*/
    if(owner == 0) //Not a targeted effect
    {
        if(currentP->spendMana(thisCard->getAbilityCost(), testing))
        {
            int counter = 0;
            while (effect[counter] != '~'){
                if (effect[counter] == 'M'){//Summon Minion
                    counter++;

                    int card = effect[counter] - '0';
                    counter++;
                    int times = effect[counter] - '0';
                    for (int i = 0; i < times; i++){
                        if (currentP->getPNum() == 1 && fieldP1.size() < 5){
                            if (card == 0){
                                fieldP1.push_back(shared_ptr<Minion>(new Minion(0,"Air Elemental",1,1,"Whoosh~")));
                            }
                        }else if (currentP->getPNum()==2 && fieldP2.size() < 5){
                            if (card == 0){
                                fieldP2.push_back(shared_ptr<Minion>(new Minion(0,"Air Elemental",1,1,"Whoosh~")));
                            }
                        }
                    }
                }else if(effect[counter] == 'R'){//Resurrect

                        if(currentP->getPNum() == 1){
                            if(fieldP1.size() == 5 || graveP1.size() == 0){
                                cout << "Cannot resurrect." << endl;
                                return false;
                            }else{
                                graveP1.back()->setDef(1);
                                fieldP1.push_back(graveP1.back());
                                graveP1.pop_back();
                            }
                        }else{
                            if(fieldP2.size() == 5 || graveP2.size() == 0){
                                cout << "Cannot resurrect." << endl;
                                return false;
                            }else{
                                graveP2.back()->setDef(1);
                                fieldP2.push_back(graveP2.back());
                                graveP2.pop_back();
                            }
                        }

                }else if (effect[counter] == 'D'){//Destroy Card
                    counter++;
                    int damage = effect[counter] - '0';
                    counter++;
                    char targ = effect[counter];
                    if(targ == 'A'){
                        if (currentP->getPNum() == 1){
                            for(int i =0; i < fieldP2.size(); i++){
                                fieldP2[i]->modDef(damage * -1);
                                  cout << "Dealt damage to: " << fieldP2[i]->getName() << "it is currently at " << fieldP2[i] ->getDef() << " defense." << endl;
                            }
                            for (int i = fieldP2.size() -1; i >= 0; i--){
                                checkDeath(2,i);
                            }
                        }else{
                            for(int i =0; i < fieldP1.size(); i++){
                                fieldP1[i]->modDef(damage* -1);
                                cout << "Dealt damage to: " << fieldP1[i]->getName() << "it is currently at " << fieldP1[i] ->getDef() << " defense." << endl;
                            }
                            for (int i = fieldP1.size() -1; i >= 0; i--){
                                checkDeath(1,i);
                            }
                        }
                    }else if (effect[counter] == 'm'){
                        counter++;
                        char modifier;
                    }
                }else if (effect[counter] == 'C'){//Increase ritual counter
                    counter++;
                    int charges = effect[counter] - '0';
                    for (int i = 0; i < charges; i ++ ){
                        if (currentP->getPNum() ==1){
                            if (ritualP1 != nullptr){
                                ritualP1->incCounter();
                            }else{
                                cout << "No Ritual in play." << endl;
                                return false;
                            }
                        }else{
                            if (ritualP2 != nullptr){
                                ritualP2->incCounter();
                            }else{
                                cout << "No Ritual in play." << endl;
                                return false;
                            }
                        }
                    }

                }else if (effect[counter] == 'P'){//Buff all minions
                    counter++;
                    int atk = effect[counter] - '0';
                    counter++;
                    int def = effect[counter] - '0';
                    if (currentP->getPNum()==1){
                        for (int i =0; i < fieldP1.size(); i++){
                            fieldP1[i]->setDef(fieldP1[i]->getDef()+ def);
                            fieldP1[i]->setAtk(fieldP1[i]->getAtk()+ atk);
                        }
                    }else{
                        for (int i =0; i < fieldP2.size(); i++){
                            fieldP2[i]->setDef(fieldP2[i]->getDef()+ def);
                            fieldP2[i]->setAtk(fieldP2[i]->getAtk()+ atk);
                        }
                    }
                }
                counter++;
            }
            if(!isTrigger) //Triggers do not use actions
                thisCard->decActions();
            return true;
        }
        else{
            cout << "Not enough mana to use this effect!" << endl;
            return false;
        }
    }
    else //Is a targeted effect
    {
        if(currentP->spendMana(thisCard->getAbilityCost(), testing))
        {
            int counter = 0;
            while (effect[counter] != '~'){
                if (effect[counter] == 'D'){//Deal Damage
                    counter++;
                    int damage = effect[counter] - '0';
                    if (owner == 1){
                        fieldP1[target -1]->modDef(damage * -1);
                        checkDeath(owner,target - 1);
                    }else{
                        fieldP2[target -1]->modDef(damage * -1);
                        checkDeath(owner,target - 1);
                    }
                }else if (effect[counter] == 'K'){//Destroy Card
                    counter++;
                    char targ = effect[counter];
                    if (targ == 'M'){
                        if(owner == 1){
                            fieldP1[target -1]->modDef(fieldP1[target -1]->getDef() * -1);
                            checkDeath(owner,target - 1);
                        }else{
                            fieldP2[target -1]->modDef(fieldP2[target -1]->getDef() * -1);
                            checkDeath(owner,target - 1);
                        }
                    }
                }else if (effect[counter] == 'U'){//Return Card to hand
                    counter++;
                    if (effect[counter] == 'M'){
                        if(owner ==1){
                          if(p1->addCard(fieldP1[target-1])){
                            fieldP1[target-1]->restoreDefaults();
                            fieldP1.erase(fieldP1.begin()+target-1);
                            triggerEffects("minleave",0,0);
                          }else{
                            fieldP1[target -1]->modDef(fieldP1[target -1]->getDef() * -1);
                            checkDeath(owner,target - 1);
                          }
                        }else{
                          if(p2->addCard(fieldP2[target-1])){
                            fieldP2[target-1]->restoreDefaults();
                            fieldP2.erase(fieldP2.begin()+target-1);
                            triggerEffects("minleave",0,0);
                          }else{
                            fieldP2[target -1]->modDef(fieldP2[target -1]->getDef() * -1);
                            checkDeath(owner,target - 1);
                          }
                        }
                    }
                }else if (effect[counter] == 'A'){//Add an action to a card
                    counter++;
                    int increment = effect[counter] - '0';
                    if (owner == 1){
                        for (int i = 0; i < increment; i++){
                            fieldP1[target-1]->incMaxActions();
                            fieldP1[target-1]->incActions();
                        }
                    }else{
                        for (int i = 0; i < increment; i++){
                            fieldP2[target-1]->incMaxActions();
                            fieldP2[target-1]->incActions();
                        }
                    }
                }else if (effect[counter] == 'B'){//Regular buff
                    counter++;
                    int atk = effect[counter] - '0';
                    counter++;
                    int def = effect[counter] - '0';
                    if (owner == 1){
                        fieldP1[target-1]->setAtk(fieldP1[target-1]->getAtk() + atk);
                        fieldP1[target-1]->setDef(fieldP1[target-1]->getDef() + def);
                    }else{
                        fieldP2[target-1]->setAtk(fieldP2[target-1]->getAtk() + atk);
                        fieldP2[target-1]->setDef(fieldP2[target-1]->getDef() + def);
                    }
                }else if (effect[counter] == 'E'){//Enchant buff
                    counter++;
                    char operation = effect[counter];
                    counter++;
                    int def = effect[counter] - '0';
                    if (operation == '+'){
                        if(owner == 1){
                            fieldP1[target-1]->setDef(fieldP1[target-1]->getDef() + def);
                        }else{
                            fieldP2[target-1]->setDef(fieldP2[target-1]->getDef() + def);
                        }
                    }else if (operation == '*'){
                        if(owner == 1){
                            fieldP1[target-1]->setDef(fieldP1[target-1]->getDef() * def);
                        }else{
                            fieldP2[target-1]->setDef(fieldP2[target-1]->getDef() * def);
                        }
                    }
                    counter++;
                    operation = effect[counter];
                    counter++;
                    int atk = effect[counter] - '0';
                     if (operation == '+'){
                        if(owner == 1){
                            fieldP1[target-1]->setAtk(fieldP1[target-1]->getAtk() + atk);
                        }else{
                            fieldP2[target-1]->setAtk(fieldP2[target-1]->getAtk() + atk);
                        }
                    }else if (operation == '*'){
                        if(owner == 1){
                            fieldP1[target-1]->setAtk(fieldP1[target-1]->getAtk() * atk);
                        }else{
                            fieldP2[target-1]->setAtk(fieldP2[target-1]->getAtk() * atk);
                        }
                    }
                }else if(effect[counter] == 'F'){//Increase Ability cost
                    counter++;
                    int upcost = effect[counter] - '0';
                     if(owner == 1){
                        if (fieldP1[target-1]->getType() == "MinionAA"){
                            fieldP1[target-1]->setAbilityCost(fieldP1[target-1]->getAbilityCost() + upcost);
                        }else{
                            cout << "The target has no ability."  << endl;
                            return false;
                        }
                    }else{
                        if (fieldP2[target-1]->getType() == "MinionAA"){
                            fieldP2[target-1]->setAbilityCost(fieldP2[target-1]->getAbilityCost() + upcost);
                        }else{
                            cout << "The target has no ability."  << endl;
                            return false;
                        }
                    }
                }else if (effect[counter] == 'S'){//Silenced
                    //Do nothing
                }else if (effect[counter] == 'd'){//Disenchant
                    //Do nothing
                    counter++;
                    int numRemove = effect[counter]- '0';
                    for (int i = 0; i < numRemove; i++){
                        if(owner==1){
                            fieldP1[target-1]->removeEnch();
                        }else{
                            fieldP2[target-1]->removeEnch();
                        }

                    }
                }
                counter++;
            }
            if(!isTrigger) //Triggers do not use actions
                thisCard->decActions();
            return true;
        }
        else{
            cout << "Not enough mana to use this effect!" << endl;
            return false;
        }
    }
}
