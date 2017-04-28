#include "singleblock.h"
#include <iostream>

using namespace std;

SingleBlock::SingleBlock(int x, int y, char type):myPos(x,y),type(type){}

void SingleBlock::down(){
    myPos.setY(myPos.getX() - 1);
}

void  SingleBlock::left(){
    myPos.setX(myPos.getX() - 1);
}

void  SingleBlock::right(){
    myPos.setX(myPos.getX() + 1);
}
void SingleBlock::setPos(int x, int y){
    myPos.setX(x);
    myPos.setY(y);
}
void SingleBlock::print(){
    cout << type;
}

int SingleBlock::returnPosX(){
    return myPos.getX();
}

int SingleBlock::returnPosY(){
    return myPos.getY();
}

char SingleBlock::getChar(){
    return type;
}



