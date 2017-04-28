#include "enchantment.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "ascii_graphics.h"
using namespace std;
Enchantment::Enchantment(int cost, string name, string desc, string effect):type{"EnchantmentNA"},cost{cost},atk{0},def{0},name{name},desc{desc},effect{effect},modifyStats{false},activated{false}{}
Enchantment::Enchantment(int cost, string atk, string def, string name, string desc, string effect):type{"EnchantmentWA"},cost{cost},atk{atk},def{def},name{name},desc{desc},effect{effect},modifyStats{true},activated{false}{}
Enchantment::~Enchantment(){}
vector<string> Enchantment::print(){
    if (modifyStats){
        return display_enchantment_attack_defence(name,cost,desc,atk,def);
    }
    return display_enchantment(name,cost,desc);
}
string Enchantment::getEffect(){
    return effect;
}
string Enchantment::getName(){
    return name;
}
string Enchantment::getType(){
    return type;
}
string Enchantment::getEnchAtk(){
    return atk;
}
void Enchantment::activate(){
    activated = true;
}
bool Enchantment::getActivated(){
    return activated;
}
string Enchantment::getEnchDef(){
    return def;
}
int Enchantment::getCost(){
    return cost;
}
int Enchantment::getAbilityCost(){
    return 0;
}
shared_ptr<Card> Enchantment::cardFactory(){
    return shared_ptr<Enchantment>(new Enchantment(*this));
}

