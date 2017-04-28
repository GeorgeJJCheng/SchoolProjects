#include "cardlist.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
using namespace std;

int main(){
	CardList library{"cards.lib"};
	library.LoadCards();
	ifstream deckBuilder("default.deck");
	string name;
	vector <shared_ptr<Card>> deck;
	while(getline(deckBuilder,name)){
		deck.push_back(library.getCard(name));
	}
	cout << deck.size() << endl;
	return 0;
}
