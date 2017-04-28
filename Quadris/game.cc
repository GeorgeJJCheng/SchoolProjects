#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include "game.h"
#include "quadblock.h"
#include "board.h"

using namespace std;

void Game::generateBlock()
{
    score = myBoard.getScore();
    if (highScore < score)
    {
        highScore = score;
    }
    int index;
    if (isRandom)
    {
        int randNum = randGen(randEngine);
        index = randNum%counter;
    }
    else
        index = 0;
    char whatsNext = myBoard.getNextBlock();
    char blockType = blockGenerator[index];
    blockGenerator.erase(blockGenerator.begin()+index, blockGenerator.begin()+index+1);
    counter--;
    myBoard.setNextBlock(blockType);
    blockType = whatsNext;
    if (blockGenerator.empty())
        refillGenerator(difficulty);
    if (blockType == 'l')
        newBlock("L");
    else if (blockType == 'j')
        newBlock("J");
    else if (blockType == 'o')
        newBlock("O");
    else if (blockType == 't')
        newBlock("T");
    else if (blockType == 's')
        newBlock("S");
    else if (blockType == 'z')
        newBlock("Z");
    else if (blockType == 'i')
        newBlock("I");
}

void Game::startGame()
{
    if (difficulty == 0 || difficulty == 1 || difficulty == 2)
    {
        gravity = false;
        starBlock = false;
    }
    else
    {
        gravity = true;
        if (difficulty >= 4)
        {
            starBlock = true;
        }
    }
    refillGenerator(difficulty);
    int index;
    int sIndex;
    if (isRandom)
    {
        int randNum = randGen(randEngine);
        index = randNum%counter;
        randNum = randGen(randEngine);
        sIndex = randNum%(counter-1);
    }
    else
    {
        index = 0;
        sIndex = 0;
    }
    char firstBlock = blockGenerator[index];
    blockGenerator.erase(blockGenerator.begin()+index, blockGenerator.begin()+index+1);
    if (blockGenerator.empty())
        refillGenerator(difficulty);
    char secondBlock = blockGenerator[sIndex];
    blockGenerator.erase(blockGenerator.begin()+sIndex, blockGenerator.begin()+sIndex+1);
    if (blockGenerator.empty())
        refillGenerator(difficulty);
    counter-=2;
    char blockType = secondBlock;
    myBoard.setNextBlock(blockType);
    blockType = firstBlock;
    if (blockGenerator.empty())
        refillGenerator(difficulty);
    if (blockType == 'l')
        newBlock("L");
    else if (blockType == 'j')
        newBlock("J");
    else if (blockType == 'o')
        newBlock("O");
    else if (blockType == 't')
        newBlock("T");
    else if (blockType == 's')
        newBlock("S");
    else if (blockType == 'z')
        newBlock("Z");
    else if (blockType == 'i')
        newBlock("I");
}

void Game::levelUp()
{
    if (difficulty < 4)
    {
        difficulty++;
        setDiff(difficulty);
        cout << "Level:          " << difficulty << endl;
        cout << "Score:          " << score << endl;
        cout << "High Score:     " << highScore << endl;
        myBoard.printBoard(graphical, xPoint);
    }
}

void Game::levelDown()
{
    if (difficulty > 0)
    {
        difficulty--;
        setDiff(difficulty);
        cout << "Level:          " << difficulty << endl;
        cout << "Score:          " << score << endl;
        cout << "High Score:     " << highScore << endl;
        myBoard.printBoard(graphical, xPoint);
    }
}

void Game::refillGenerator(int diff)
{
    blockGenerator.clear();
    if (diff == 0 || isRandom == false)
    {
        counter = 0;
        ifstream fixedFile(noRandFile);
        string temp;
        while (fixedFile >> temp)
        {
            blockGenerator.push_back(temp[0]);
            counter++;
        }
	cout << endl;
    }
    else if (diff == 1)
    {
        blockGenerator.push_back('s');
        blockGenerator.push_back('z');
        blockGenerator.push_back('i');
        blockGenerator.push_back('i');
        blockGenerator.push_back('j');
        blockGenerator.push_back('j');
        blockGenerator.push_back('l');
        blockGenerator.push_back('l');
        blockGenerator.push_back('o');
        blockGenerator.push_back('o');
        blockGenerator.push_back('t');
        blockGenerator.push_back('t');
        counter = 12;
    }
    else if (diff == 2)
    {
        blockGenerator.push_back('s');
        blockGenerator.push_back('z');
        blockGenerator.push_back('i');
        blockGenerator.push_back('j');
        blockGenerator.push_back('l');
        blockGenerator.push_back('o');
        blockGenerator.push_back('t');
        counter = 7;
    }
    else
    {
        blockGenerator.push_back('s');
        blockGenerator.push_back('s');
        blockGenerator.push_back('z');
        blockGenerator.push_back('z');
        blockGenerator.push_back('i');
        blockGenerator.push_back('j');
        blockGenerator.push_back('l');
        blockGenerator.push_back('o');
        blockGenerator.push_back('t');
        counter = 9;
    }
}

void Game::restart()
{
    myBoard.clearBoard();
    score = 0;
    cout << "Game restarted. Current difficulty is " << difficulty << "." << endl;
    refillGenerator(difficulty);
    startGame();
}

bool Game::boardBehavior()
{
    bool hasBehavior = false;
    if (gravity == true)
    {
        int result = myBoard.checkState(difficulty);
        if (result == 1)
        {
            generateBlock();
        }
        else
        {
            myBoard.bDown();
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            myBoard.printBoard(graphical, xPoint);
        }
        myBoard.updateHeight();
        hasBehavior = true;
    }
    return hasBehavior;
}

void Game::setFile(string file)
{
    noRandFile = file;
}

int Game::getDiff()
{
    return difficulty;
}

void Game::setDiff(int diff)
{
    if (diff == 0 || diff == 1 || diff == 2)
    {
        if (diff == 0)
            isRandom = false;
        else
            isRandom = true;
        starBlock = false;
        gravity = false;
    }
    else if (diff == 3)
    {
        isRandom = true;
        starBlock = false;
        gravity = true;
    }
    else
    {
        isRandom = true;
        starBlock = true;
        gravity = true;
    }
    refillGenerator(diff);
}

void Game::checkLeft()
{
    if (!myBoard.checkLeft())
    {
        myBoard.bLeft();
        if (!boardBehavior())
        {
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            myBoard.printBoard(graphical, xPoint);
        }
    }
}
void Game::checkRight()
{
    if (!myBoard.checkRight())
    {
        myBoard.bRight();
        if(!boardBehavior())
        {
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            myBoard.printBoard(graphical, xPoint);
        }
    }
}
void Game::checkDown()
{
    if (!myBoard.checkDown())
    {
        myBoard.bDown();
        if(!boardBehavior())
        {
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            myBoard.printBoard(graphical, xPoint);
        }
    }
    else
    {
        int result = myBoard.checkState(difficulty);
        if (result == 1)
        {
            myBoard.updateHeight();
            generateBlock();
        }
        else
        {
            if (!boardBehavior())
            {
                cout << "Level:          " << difficulty << endl;
                cout << "Score:          " << score << endl;
                cout << "High Score:     " << highScore << endl;
                myBoard.printBoard(graphical, xPoint);
            }
        }
    }
}

void Game::checkCRot()
{
    if (myBoard.clock())
    {
        int result = myBoard.checkState(difficulty);
        if (result == 1)
        {
            generateBlock();
        }
        else
        {
            if(!boardBehavior())
            {
                cout << "Level:          " << difficulty << endl;
                cout << "Score:          " << score << endl;
                cout << "High Score:     " << highScore << endl;
                myBoard.printBoard(graphical, xPoint);
            }
        }
    }
}
void Game::checkCCRot()
{
    if (myBoard.cClock())
    {
        int result = myBoard.checkState(difficulty);
        if (result == 1)
        {
            generateBlock();
        }
        else
        {
            if(!boardBehavior())
            {
                cout << "Level:          " << difficulty << endl;
                cout << "Score:          " << score << endl;
                cout << "High Score:     " << highScore << endl;
                myBoard.printBoard(graphical, xPoint);
            }
        }
    }
}

void Game::dropBlock()
{
    while (myBoard.checkState(difficulty) == 0)
    {
        myBoard.bDown();
    }
    myBoard.updateHeight();
    generateBlock();
}

void Game::setSeed(int mySeed)
{
    randEngine.seed(mySeed);
}

void Game::newBlock(string type)
{
    bool lost = false;
    if (type == "S")
    {
        if (myBoard.returnInd(0) >= 13 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 14)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "Z")
    {
        if (myBoard.returnInd(0) >= 14 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 13)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "I")
    {
        if (myBoard.returnInd(0) >= 14 || myBoard.returnInd(1) >= 14 || myBoard.returnInd(2) >= 14 || myBoard.returnInd(3) >= 14)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "L" || type == "J")
    {
        if (myBoard.returnInd(0) >= 13 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 13)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "T")
    {
        if (myBoard.returnInd(0) >= 14 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 14)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "O")
    {
        if (myBoard.returnInd(0) >= 13 || myBoard.returnInd(1) >= 13)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    if (lost == false)
    {
        myBoard.setActive(type);
        cout << "Level:          " << difficulty << endl;
        cout << "Score:          " << score << endl;
        cout << "High Score:     " << highScore << endl;
        myBoard.printBoard(graphical, xPoint);
    }
}

void Game::setBlock(string type)
{
    bool lost = false;
    if (type == "S")
    {
        if (myBoard.returnInd(0) >= 13 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 14)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "Z")
    {
        if (myBoard.returnInd(0) >= 14 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 13)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "I")
    {
        if (myBoard.returnInd(0) >= 14 || myBoard.returnInd(1) >= 14 || myBoard.returnInd(2) >= 14 || myBoard.returnInd(3) >= 14)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "L" || type == "J")
    {
        if (myBoard.returnInd(0) >= 13 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 13)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "T")
    {
        if (myBoard.returnInd(0) >= 14 || myBoard.returnInd(1) >= 13 || myBoard.returnInd(2) >= 14)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    else if (type == "O")
    {
        if (myBoard.returnInd(0) >= 13 || myBoard.returnInd(1) >= 13)
        {
            cout << "___________________________" << endl;
            cout << endl;
            cout << "         You lost!         " << endl;
            cout << "___________________________" << endl;
            cout << "Level:          " << difficulty << endl;
            cout << "Score:          " << score << endl;
            cout << "High Score:     " << highScore << endl;
            lost = true;
            restart();
        }
    }
    if (lost == false)
    {
        myBoard.setNewActive(type);
        cout << "Level:          " << difficulty << endl;
        cout << "Score:          " << score << endl;
        cout << "High Score:     " << highScore << endl;
        myBoard.printBoard(graphical, xPoint);
    }
}

void Game::startHint()
{
    myBoard.getHint();
    myBoard.printBoard(graphical, xPoint);
}

void Game::switchRandom(bool r)
{
    isRandom = r;
}

Game::Game(int diff, bool graphical, Xwindow* xP): randGen(0, 251), starBlock(false), gravity(false), score(0), highScore(0), noRandFile("sequence.txt"),  difficulty(diff), counter(0), isRandom(true), graphical(graphical), xPoint(xP)
{
    randEngine.seed(time(NULL));
    //setDiff(difficulty);
}
