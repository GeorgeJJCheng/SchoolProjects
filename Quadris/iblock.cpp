#include "iblock.h"

IBlock::IBlock():type('I'),orientation(1){
    blockArray[0] = new SingleBlock(0,14,type);
    blockArray[1] = new SingleBlock(1,14,type);
    blockArray[2] = new SingleBlock(2,14,type);
    blockArray[3] = new SingleBlock(3,14,type);
}

IBlock::IBlock(const IBlock &other ){
    type = other.type;
    orientation = other.orientation;
    for (int i = 0; i < 4; i++){
        blockArray[i] = new SingleBlock(other.blockArray[i]->returnPosX(),other.blockArray[i]->returnPosY(),type);
    }
}

IBlock::~IBlock(){
    for (int i = 0; i < 4; i++){
        delete blockArray[i];
    }
}

void IBlock::ccRotate(){
    this -> cRotate();

}

void IBlock::cRotate(){

     switch(orientation){

        case 1:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX(),blockArray[0]->returnPosY());
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 1, blockArray[1]->returnPosY() + 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 2, blockArray[2]->returnPosY() + 2);
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 3, blockArray[3]->returnPosY() + 3);
            break;
        case 2:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX(),blockArray[0]->returnPosY());
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 1, blockArray[1]->returnPosY() - 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 2, blockArray[2]->returnPosY() - 2);
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 3, blockArray[3]->returnPosY() - 3);
            break;
        default: break;
    }

}

void  IBlock::left(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() - 1, blockArray[x]->returnPosY());
    }
}

void IBlock::right(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() + 1, blockArray[x]->returnPosY());
    }
}


void IBlock::down(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX(), blockArray[x]->returnPosY() - 1);
    }
}

void IBlock::drop(){
//TODO:KETE
}

int IBlock::getPosX(int i){
    return blockArray[i]->returnPosX();
}

int IBlock::getPosY(int i){
    return blockArray[i]->returnPosY();
}

char IBlock::getType(){
    return type;
}

void IBlock::print(){
    for (int i = 0; i < 4; i++){
        blockArray[i]->print();
    }
}

QuadBlock* IBlock::blockFactory(){
    return new IBlock(*this);
}


