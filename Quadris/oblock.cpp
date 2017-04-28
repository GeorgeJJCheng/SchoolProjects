#include "oblock.h"

OBlock::OBlock():type('O'),orientation(1){
    blockArray[0] = new SingleBlock(0,14,type);
    blockArray[1] = new SingleBlock(1,14,type);
    blockArray[2] = new SingleBlock(0,13,type);
    blockArray[3] = new SingleBlock(1,13,type);
}

OBlock::OBlock(const OBlock &other ){
    type = other.type;
    orientation = other.orientation;
    for (int i = 0; i < 4; i++){
        blockArray[i] = new SingleBlock(other.blockArray[i]->returnPosX(),other.blockArray[i]->returnPosY(),type);
    }
}

OBlock::~OBlock(){
    for (int i = 0; i < 4; i++){
        delete blockArray[i];
    }
}

void OBlock::ccRotate(){
    return;
}

void OBlock::cRotate(){
    return;
}

void OBlock::left(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() - 1, blockArray[x]->returnPosY());
    }
}

void OBlock::right(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() + 1, blockArray[x]->returnPosY());
    }
}


void OBlock::down(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX(), blockArray[x]->returnPosY() - 1);
    }
}

int OBlock::getPosX(int i){
    return blockArray[i]->returnPosX();
}

int OBlock::getPosY(int i){
    return blockArray[i]->returnPosY();
}

char OBlock::getType(){
    return type;
}

void OBlock::drop(){
//TODO: Kete
}

void OBlock::print(){
    for (int i = 0; i < 4; i++){
        blockArray[i]->print();
    }
}

QuadBlock* OBlock::blockFactory(){
    return new OBlock(*this);
}


