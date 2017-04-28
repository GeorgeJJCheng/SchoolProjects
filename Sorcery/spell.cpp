#include "spell.h"
#include <iostream>
#include <vector>
#include "ascii_graphics.h"
using namespace std;
Spell::Spell(int cost, string name, string desc, string effect, bool targeted):type{"Spell"},cost{cost},name{name},desc{desc},effect{effect},targeted{targeted}{
    if (targeted){
        type = "SpellT";
    }
}
Spell::~Spell(){}
vector<string> Spell::print(){
    return display_spell(name,cost,desc);
}
string Spell::getEffect(){
    return effect;
}
string Spell::getName(){
    return name;
}
string Spell::getType(){
    return type;
}
int Spell::getCost(){
    return cost;
}
int Spell::getAbilityCost(){
    return 0;
}
shared_ptr<Card> Spell::cardFactory(){
    return shared_ptr<Spell>(new Spell(*this));
}
