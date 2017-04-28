#include "sblock.h"

SBlock::SBlock():type('S'),orientation(1){
    blockArray[0] = new SingleBlock(0,13,type);
    blockArray[1] = new SingleBlock(1,13,type);
    blockArray[2] = new SingleBlock(1,14,type);
    blockArray[3] = new SingleBlock(2,14,type);
}

SBlock::SBlock(const SBlock &other ){
    type = other.type;
    orientation = other.orientation;
    for (int i = 0; i < 4; i++){
        blockArray[i] = new SingleBlock(other.blockArray[i]->returnPosX(),other.blockArray[i]->returnPosY(),type);
    }
}

SBlock::~SBlock(){
    for (int i = 0; i < 4; i++){
        delete blockArray[i];
    }
}

void SBlock::ccRotate(){
    this -> cRotate();

}

void SBlock::cRotate(){

     switch(orientation){

        case 1:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX(), blockArray[0]->returnPosY() + 2);
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 1, blockArray[1]->returnPosY() + 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 1, blockArray[3]->returnPosY() - 1);
            break;
        case 2:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX(), blockArray[0]->returnPosY() - 2);
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 1, blockArray[1]->returnPosY() - 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 1, blockArray[3]->returnPosY() + 1);
            break;
        default: break;
    }

}

void  SBlock::left(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() - 1, blockArray[x]->returnPosY());
    }
}

void SBlock::right(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() + 1, blockArray[x]->returnPosY());
    }
}

int SBlock::getPosX(int i){
    return blockArray[i]->returnPosX();
}

int SBlock::getPosY(int i){
    return blockArray[i]->returnPosY();
}

char SBlock::getType(){
    return type;
}


void SBlock::down(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX(), blockArray[x]->returnPosY() - 1);
    }
}

void SBlock::drop(){
//TODO:KETE
}

void SBlock::print(){
    for (int i = 0; i < 4; i++){
        blockArray[i]->print();
    }
}

QuadBlock* SBlock::blockFactory(){
    return new SBlock(*this);
}


