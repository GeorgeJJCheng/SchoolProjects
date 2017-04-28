#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <random>
#include <time.h>
#include "player.h"
#include "cardlist.h"

using namespace std;

Player::Player()
{
    //ctor
}

Player::Player(int pNum, string name, string decklist): canMull(true), randGen(0, 239), pNum(pNum), maxHP(30), hp(30), decklist(decklist), name(name)
{
    if(pNum == 1)
    {
        curMana = 2;
        maxMana = 2;
    }
    else
    {
        curMana = 3;
        maxMana = 3;
    }
    seed = time(NULL);
    randEngine.seed(seed+pNum);
}

Player::~Player()
{
    //dtor, shared_ptrs implemented, no longer needed?
    /*
    for(int i = 0; i < hand.size(); i++)
        hand.pop_back();
    for(int i = 0; i < deck.size(); i++)
        deck.pop_back();
    */
}

void Player::fillDeck()
{
    //ifstream deckSource(decklist);
    //Interpret card data
    CardList library("cards.lib");
	library.LoadCards();
	ifstream deckBuilder(decklist);
	string name;
	while(getline(deckBuilder,name)){
        if(library.getCard(name))
            deck.push_back(library.getCard(name));
	}
    //shuffleDeck();
}

void Player::shuffleDeck()
{
    randEngine.seed(time(NULL)+pNum);
    vector <shared_ptr<Card>> newDeck;
    int n = deck.size();
    for(int i = 0; i < n; i++)
    {
        int randNum = randGen(randEngine);
        randNum = randNum%deck.size();
        newDeck.push_back(deck[randNum]);
        deck[randNum] = nullptr;
        deck.erase(deck.begin()+randNum);
    }
    deck = newDeck;
}
bool Player::addCard(shared_ptr<Card>card){
    if(hand.size() <= 10){
        hand.push_back(card);
        return true;
    }
    return false;
}

void Player::draw(int n)
{
    for(int i = 0; i < n; i++)
    {
       //Player loses (?) if deck is currently empty, else draws a card.
        if(deck.size() != 0)
        {
            hand.push_back(deck.back());
            deck.pop_back();
        }
    }
}

shared_ptr<Card> Player::discard(int i)
{
    shared_ptr<Card> temp = hand[i];
    hand.erase(hand.begin() + i);
    return temp;
}

void Player::startTurn()
{
    if(maxMana != 10)
        maxMana++;
    curMana = maxMana;
    draw(1);
}

void Player::setSeed(int s)
{
    randEngine.seed(s);
}

string Player::getName()
{
    return name;
}

int Player::getHP()
{
    return hp;
}

int Player::getCurMana()
{
    return curMana;
}

int Player::getMaxMana()
{
    return maxMana;
}

int Player::getPNum()
{
    return pNum;
}

int Player::getHandSize()
{
    return hand.size();
}

shared_ptr<Card> Player::getCard(int c)
{
    return hand[c];
}

void Player::modHP(int n)
{
    if(hp + n > maxHP)
        hp = maxHP;
    else
        hp += n;
}

bool Player::spendMana(int n, bool testing)
{
    if(n > curMana)
    {
        if(testing)
        {
            curMana = 0;
            return true;
        }
        else
            return false;
    }
    else
    {
        curMana -= n;
        return true;
    }
}

void Player::mulligan(vector<int> indexes)
{
    for(int i = 0; i < indexes.size(); i++)
    {
        if(indexes[i] < hand.size())
        {
            deck.push_back(hand[indexes[i]]);
            hand.erase(hand.begin()+indexes[i]);
            for(int j = 0; j < indexes.size(); j++)
            {
                if(indexes[j] > indexes[i])
                    indexes[j]--;
            }
        }
    }
    shuffleDeck();
    draw(indexes.size());
    canMull = false;
}

bool Player::getMull()
{
    return canMull;
}

void Player::noMull()
{
    canMull = false;
}

void Player::printDeck()
{
    for(int i = deck.size()-1; i >= 0; i--)
    {
        cout << deck[i]->getName() << endl;
    }
}

void Player::builddeck()
{
    cout << "What would you like to name your deck?" << endl;
    string deckname;
    cin >> deckname;
    ofstream myDeck(deckname+".deck");
    cout << name << ", please select from the following list of cards to build your deck. Enter the names of the cards to add them to your deck." << endl;
    cout << "Be careful with spelling and capitalization. Type end to stop deck building." << endl;
    ifstream lib("cards.lib");
    string name;
    while(getline(lib, name))
    {
        for(int i = 0; i < name.length(); i++)
        {
            if(name[i] == '_')
                name[i] = ' ';
        }
        cout << name << endl;
        getline(lib, name);
        getline(lib, name);
    }
    cout << endl << "[Enter the names of your cards below.]" << endl << endl;
    string card;
    while(getline(cin, card))
    {
        if(card == "end")
            break;
        myDeck << card << endl;
    }
    decklist = deckname+".deck";
    myDeck.close();
}
