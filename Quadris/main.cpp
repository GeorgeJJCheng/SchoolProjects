#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "game.h"
#include "quadblock.h"

using namespace std;

int main(int argc, char* argv[])
{
    string noRandFile = "sequence.txt";
    bool graphical = true;
    int startLevel = 0;
    int genSeed = 0;
    Xwindow* windowP = nullptr;
    for (int i = 1; i < argc; i++)
    {
        stringstream ss;
        ss << argv[i];
        string comp;
        ss >> comp;
        if (comp == "-text")
        {
            graphical = false;
        }
        else if (comp == "-seed")
        {
            stringstream temp;
            temp << argv[i+1];
            temp >> genSeed;
            i++;
        }
        else if (comp == "-scriptfile")
        {
            if (i+1 < argc)
            {
                stringstream temp;
                temp << argv[i+1];
                temp >> noRandFile;
                i++;
            }
            else
            {
                cout << "No script file name provided!" << endl;
            }
        }
        else if (comp == "-startlevel")
        {
            if (i+1 < argc)
            {
                stringstream temp;
                temp << argv[i+1];
                temp >> startLevel;
                i++;
            }
            else
            {
                cout << "No level number provided!" << endl;
            }
        }
    }
    if (graphical)
    {
        windowP = new Xwindow();
    }
    //Command line initialization complete
    Game myGame(startLevel, graphical, windowP);
    myGame.setFile(noRandFile);
    myGame.setSeed(genSeed);
    myGame.startGame();
    string command;
    while (cin >> command)
    {
        int timesExecuted = 1;
        stringstream ss;
        ss << command;
        if (ss >> timesExecuted)
        {
            cin >> command;
        }
        else
        {
            timesExecuted = 1;
            ss >> command;
        }
        for (int i = 0; i < timesExecuted; i++)
        {
            if (command == "l" || command == "left" || command == "lef")
                myGame.checkLeft();
            else if (command == "r" || command == "right" || command == "ri")
                myGame.checkRight();
            else if (command == "d" || command == "down" || command == "do")
                myGame.checkDown();
            else if (command == "c" || command == "clockwise" || command == "cl")
                myGame.checkCRot();
            else if (command == "cc" || command == "counterclockwise" || command == "co")
                myGame.checkCCRot();
            else if (command == "dr" || command == "drop")
                myGame.dropBlock();
            else if (command == "levelup" || command == "lvu" || command == "levelu")
                myGame.levelUp();
            else if (command == "leveldown" || command == "lvd" || command == "leveld")
                myGame.levelDown();
            else if (command == "norandom" || command == "n")
            {
                string fileName;
                cin >> fileName;
                myGame.setFile(fileName);
                myGame.switchRandom(false);
                myGame.refillGenerator(0);
            }
            else if (command == "random" || command == "ra")
            {
                myGame.setFile("sequence.txt.");
                myGame.switchRandom(true);
                myGame.refillGenerator(myGame.getDiff());
            }
            else if (command == "sequence" || command == "s")
            {
                string fileName;
                cin >> fileName;
                myGame.setFile(fileName);
            }
            else if (command == "I" || command == "J" || command == "L" || command == "S" || command == "Z" || command == "O" || command == "T")
                myGame.setBlock(command);
            else if (command == "restart" || command == "re")
                myGame.restart();
            else if (command == "hint" || command == "h")
                myGame.startHint();
            else
                cout << "Invalid command." << endl;
        }
    }
}
