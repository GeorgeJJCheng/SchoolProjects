#ifndef __GAME__H__
#define __GAME__H__

#include <string>
#include <vector>
#include <random>
#include "board.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "oblock.h"
#include "tblock.h"

class Game
{
private:
    std::mt19937 randEngine;
    std::uniform_int_distribution <int> randGen;
    int seed;
    bool starBlock;
    bool gravity;
    Board myBoard;
    int score;
    int highScore;
    std::vector <char> blockGenerator;
    std::string noRandFile;
    int difficulty;
    int counter;
    bool isRandom;
    bool graphical;
    Xwindow* xPoint;

public:
    Game(int diff, bool graphical, Xwindow* xP);
    int getDiff();
    void generateBlock();
    bool boardBehavior();
    void levelUp();
    void levelDown();
    void refillGenerator(int diff);
    void restart();
    void setDiff(int diff);
    void setFile(std::string file);
    void checkLeft();
    void checkRight();
    void checkDown();
    void checkCRot();
    void checkCCRot();
    void dropBlock();
    void setSeed(int mySeed);
    void setBlock(std::string type);
    void newBlock(std::string type);
    void startHint();
    void switchRandom(bool r);
    void startGame();
};

#endif // __GAME__H__
