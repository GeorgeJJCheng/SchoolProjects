#include "card.h"
#include <vector>
#include <memory>
using namespace std;

Card::~Card(){}
vector<string> Card::print(){vector<string> s; return s;}
string Card::getEffect(){return "";}
string Card::getName(){return "";}
string Card::getType(){return "";}
string Card::getTrigger(){return "";}
string Card::getEnchAtk(){return "";}
string Card::getEnchDef(){return "";}
int Card::getDef(){return -69;}
int Card::getAtk(){return -69;}
int Card::getOrigDef(){return -69;}
int Card::getOrigAtk(){return -69;}
int Card::getCost(){return -69;}
int Card::getAbilityCost(){return -69;}
int Card::getRitCounter(){return -69;}
int Card::getRitCost(){return -69;}
int Card::getActions(){return -69;}
bool Card::getTarget(){return false;}
void Card::setAtk(int atk){}
void Card::setDef(int def){}
void Card::setActions(int action){}
void Card::modDef(int card){}
void Card::countDown(){}
void Card::decActions(){}
void Card::incActions(){}
void Card::incCounter(){}
int  Card::getMaxActions(){return -69;}
void Card::incMaxActions(){}//fucksss
int  Card::getNumEnch(){return -69;}
shared_ptr<Card> Card::getEnch(int i){return nullptr;}
shared_ptr<Card> Card::cardFactory(){return nullptr;}
bool Card::getActivated(){return false;}
void Card::activate(){//fuck
}
void Card::addEnch(shared_ptr<Card>enchantment){//I can't believe you've done this
}
void Card::setAbilityCost(int a){}
void Card::removeEnch(){}
void Card::restoreDefaults(){}

