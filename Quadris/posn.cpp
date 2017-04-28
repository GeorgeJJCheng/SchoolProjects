#include "posn.h"

Posn::Posn(int x, int y):xPos(x),yPos(y){}

int Posn::getX(){
    return xPos;
}

int Posn::getY(){
    return yPos;
}

void Posn::setX(int x){
    xPos = x;
}

void Posn::setY(int y){
    yPos = y;
}

