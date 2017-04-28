#include <string>
#include <iostream>
#include <sstream>
#include "game.h"

using namespace std;

int main(int argc, char* argv[]){
    string d1 = "default.deck";
    string d2 = "default.deck";
    string init = "default";
    bool testing = false;
    bool deckbuilder = false;
    for(int i = 0; i < argc; i++)
    {
        stringstream ss;
        ss << argv[i];
        string comp;
        ss >> comp;
        if(comp == "-deck1")
        {
            stringstream ds;
            ds << argv[i+1];
            ds >> d1;
            i++;
        }
        else if(comp == "-deck2")
        {
            stringstream ds;
            ds << argv[i+1];
            ds >> d2;
            i++;
        }
        else if(comp == "-init")
        {
            stringstream ss;
            ss << argv[i+1];
            ss >> init;
            i++;
            //read a file and pass commands to game
        }
        else if(comp == "-testing")
        {
            //run testing mode
            testing = true;
        }
        else if(comp == "-deckbuilder")
        {
            deckbuilder = true;
        }
    }
    Game thisGame(d1, d2, init, testing, deckbuilder); //Pass decknames if command line argument -deck1/-deck2 is called.
    thisGame.init();
}
