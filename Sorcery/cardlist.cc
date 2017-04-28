#include "cardlist.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
CardList::CardList(std::string filename):filename{filename}{}
CardList::~CardList(){}
void CardList::LoadCards()
{
    ifstream cardReader{filename};
    string s;
    string name;
    int cost;
    string desc;
    string effect;
    char type;
    while (cardReader >> name){
		 for (int i = 0; i < name.size(); i++){
            if (name[i] == '_'){
                name[i] = ' ';
			}
         }
         cardReader >> cost;
         cardReader >> desc;
         for (int i = 0; i < desc.size(); i++){
            if (desc[i] == '@'){
                desc[i] = ' ';
            }
         }
         cardReader >> effect;
         cardReader >> type;
         string effstatus;

         switch(type){
            case 'm':{
                int atk;
                int def;
                cardReader >> atk;
                cardReader >> def;
                cardReader >> effstatus;
                if (effstatus == "None"){
					cout << "Loaded Normal Minion: " << name << endl;
                    auto m = make_shared<Minion> (cost,name,atk,def,desc);
                    library.emplace_back(m);
                }else if(effstatus == "Triggered"){
					cout << "Loaded Trigger Effect Minion: " << name << endl;
                    string trigger;
                    cardReader >> trigger;
					auto m = make_shared<Minion>(cost,name,desc,effect,def,atk,trigger);
                    library.emplace_back(m);
                }else if (effstatus == "Activated"){
					cout << "Loaded Activated Effect Minion: " << name << endl;
                    int effCost;
                    cardReader >> effCost;
					auto m = make_shared<Minion>(cost,name,desc,effect,def,atk,effCost,false);
                    library.emplace_back(m);
                }else{
                    cout << "Loaded Activated Effect Target Minion: " << name << endl;
                    int effCost;
                    cardReader >> effCost;
					auto m = make_shared<Minion>(cost,name,desc,effect,def,atk,effCost,true);
                    library.emplace_back(m);
                }
                break;
            }
            case 's':{
                 string spelltype;
                 cardReader >> spelltype;
                 if (spelltype == "A"){
                     cout << "Loaded Activated Spell: " << name << endl;
                     auto s = make_shared<Spell>(cost,name,desc,effect,false);
                     library.emplace_back(s);
                 }else{
                     cout << "Loaded Targeted Spell: " << name << endl;
                     auto s = make_shared<Spell>(cost,name,desc,effect,true);
                     library.emplace_back(s);
                 }
                break;
            }
            case 'e':{
                cardReader >> effstatus;
                if (effstatus == "Stats"){
                    cout << "Loaded Enchantment w/ atk/def: " << name << endl;
                    string atk;
                    string def;
                    cardReader >> atk;
                    cardReader >> def;
                    auto e = make_shared<Enchantment>(cost,atk,def,name,desc,effect);
                    library.emplace_back(e);
                }else{
                    cout << "Loaded Enchantment: " << name << endl;
                    auto e = make_shared<Enchantment>(cost,name,desc,effect);
                    library.emplace_back(e);
                }
                break;
            }
            case 'r':{
                cout << "Loaded Ritual: " << name << endl;
                int counter;
                int ritcost;
                string trigger;
                cardReader >> ritcost;
                cardReader >> counter;
                cardReader >> trigger;
                auto r = make_shared<Ritual>(cost,name,ritcost,desc,effect,counter,trigger);
                library.emplace_back(r);
                break;
            }
            default:
                break;
		}
    }
}
shared_ptr<Card> CardList::getCard(std::string name)
{
    for (int i = 0; i < library.size(); i++){
		if(library[i]->getName() == name){
            return library[i]->cardFactory();
		}
    }
	return nullptr;
}
