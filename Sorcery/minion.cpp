#include "minion.h"
#include <iostream>
#include <vector>
#include "ascii_graphics.h"
using namespace std;

Minion::~Minion(){
}
Minion::Minion(int cost, std::string name, std::string desc, std::string effect, int def, int atk, string trigger):type{"MinionWA"},cost{cost},name{name},desc{desc},effect{effect},actions{0},def{def},atk{atk},trigger{trigger}{
    origdef = def;
    origatk = atk;
    origeffcost = effCost;
    origcost = cost;
    effCost = 0;
    origeffect = effect;
    hasEffect = true;
    hasEffCost = false;
    maxActions = 1;

}
Minion::Minion(int cost, std::string name, std::string desc, std::string effect, int def, int atk, int effCost, bool targeted):type{"MinionAA"},cost{cost},name{name},desc{desc},effect{effect},actions{0},def{def},atk{atk},effCost{effCost},targeted{targeted}{
    origdef = def;
    origatk = atk;
    origeffect = effect;
    trigger = "";
    hasEffect = true;
    hasEffCost = true;
    maxActions = 1;
    origeffcost = effCost;
    origcost = cost;

}
Minion::Minion(int cost, std::string name, int def, int atk,std::string desc):type{"MinionNA"},cost{cost},name{name},desc{desc},actions{0},def{def},atk{atk}{
    //desc = "";
    origdef = def;
    origatk = atk;
    effCost = 0;
    origeffect = effect;
    trigger = "";
    hasEffect = false;
    hasEffCost = false;
    maxActions = 1;
    origeffcost = 0;
    origcost = cost;

}
Minion::Minion(const Minion &other):type{other.type},cost{other.cost},name{other.name},desc{other.desc},effect{other.effect},actions{0},def{other.def},atk{other.atk},targeted{other.targeted}{
    origdef = other.def;
    origatk = other.atk;
    origeffect = other.effect;
    trigger = other.trigger;
    effCost = other.effCost;
    hasEffect = other.hasEffect;
    hasEffCost = other.hasEffCost;
    maxActions = other.maxActions;

}
string Minion::getName(){
    return name;
}
vector<string> Minion::print(){
    vector<string> tmpCard;
    if (!hasEffect){
        tmpCard = display_minion_no_ability(name, cost, atk, def, desc);
    }else{
        if(!hasEffCost){
            tmpCard = display_minion_triggered_ability(name,cost,atk,def,desc);
        }else{
            tmpCard = display_minion_activated_ability(name,cost,atk,def,effCost,desc);
        }
    }
    return tmpCard;
}
void Minion::setAtk(int atk){
    this -> atk = atk;
}
void Minion::setDef(int def){
    this -> def = def;
}
int Minion::getActions(){
    return actions;
}
int Minion::getAtk(){
    return atk;
}
int Minion::getDef(){
    return def;
}
int Minion::getAbilityCost(){
    return effCost;
}
bool Minion::getTarget(){
    return targeted;
}
int Minion::getCost(){
    return cost;
}
string Minion::getEffect(){
    return effect;
}
string Minion::getTrigger()
{
    return trigger;
}
void Minion::applyMods(){
    //TODO: Apply Modifiers
}
void Minion::modDef(int mod){
    def = def + mod;
}
string Minion::getType(){
    return type;
}
void Minion::incActions(){
    actions++;
}
void Minion::decActions(){
    actions--;
}

int Minion::getNumEnch()
{
    return modifiers.size();
}
shared_ptr<Card> Minion::getEnch(int i)
{
    if(i == -1){
        return modifiers.back();
    }else{
        return modifiers[i];
    }
}
int Minion::getOrigDef(){
    return origdef;
}
int Minion::getOrigAtk(){return origatk;}

shared_ptr<Card> Minion::cardFactory(){
    return shared_ptr<Minion>(new Minion(*this));
}
void Minion::addEnch(shared_ptr<Card> enchantment){
    modifiers.push_back(enchantment);
}
void Minion::removeEnch(){
    modifiers.pop_back();
}
int Minion::getMaxActions()
{
    return maxActions;
}
void Minion::setActions(int a)
{
    actions = a;
}
void Minion::setAbilityCost(int a)
{
    effCost = a;
}
void Minion::incMaxActions()
{
    maxActions++;
}
void Minion::restoreDefaults(){
    for(int i = 0; i < modifiers.size(); i++){
        removeEnch();
    }
    atk = origatk;
    def = origdef;
    effCost = origeffcost;
    cost = origcost;
}

