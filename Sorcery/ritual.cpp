#include "ritual.h"
#include <iostream>
#include <vector>
#include "ascii_graphics.h"
using namespace std;
Ritual::Ritual(int cost, string name,int ritcost, string desc, string effect, int counter, string trigger):type{"Ritual"},cost{cost},ritcost{ritcost},name{name},desc{desc},effect{effect},counter{counter},trigger{trigger}{}
Ritual::~Ritual(){}
vector<string> Ritual::print(){
    return display_ritual(name,cost,ritcost,desc,counter);
}
string Ritual::getEffect(){
    return effect;
}
string Ritual::getName(){
    return name;
}
string Ritual::getType(){
    return type;
}
int Ritual::getCost(){
    return cost;
}
string Ritual::getTrigger(){
    return trigger;
}
int Ritual::getRitCost(){
    return ritcost;
}
int Ritual::getRitCounter(){
    return counter;
}
void Ritual::countDown(){
    counter--;
}
void Ritual::incCounter(){
    counter++;
}
int Ritual::getAbilityCost(){
    return ritcost;
}
shared_ptr<Card> Ritual::cardFactory(){
    return shared_ptr<Ritual>(new Ritual(*this));
}
