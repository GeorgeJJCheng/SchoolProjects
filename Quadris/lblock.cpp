#include "lblock.h"

LBlock::LBlock():type('L'),orientation(1){
    blockArray[0] = new SingleBlock(0,13,type);
    blockArray[1] = new SingleBlock(1,13,type);
    blockArray[2] = new SingleBlock(2,13,type);
    blockArray[3] = new SingleBlock(2,14,type);
}

LBlock::LBlock(const LBlock &other ){
    type = other.type;
    orientation = other.orientation;
    for (int i = 0; i < 4; i++){
        blockArray[i] = new SingleBlock(other.blockArray[i]->returnPosX(),other.blockArray[i]->returnPosY(),type);
    }
}

LBlock::~LBlock(){
    for (int i = 0; i < 4; i++){
        delete blockArray[i];
    }
}

void LBlock::ccRotate(){
    switch(orientation){

        case 1:
            orientation = 4;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 1, blockArray[0]->returnPosY());
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY() + 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 1, blockArray[2]->returnPosY() + 2);
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 2, blockArray[3]->returnPosY() + 1);
            break;
        case 2:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX(), blockArray[0]->returnPosY() - 2);
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 1, blockArray[1]->returnPosY() - 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 2, blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 1, blockArray[3]->returnPosY() + 1);
            break;
        case 3:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 2, blockArray[0]->returnPosY() + 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 1, blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY() - 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 1, blockArray[3]->returnPosY());
            break;
        case 4:
            orientation = 3;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 1, blockArray[0]->returnPosY() + 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 1, blockArray[2]->returnPosY() - 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX(), blockArray[3]->returnPosY() - 2);
            break;
        default: break;
    }

}

void LBlock::cRotate(){

     switch(orientation){

        case 1:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX(), blockArray[0]->returnPosY() + 2);
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 1, blockArray[1]->returnPosY() + 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 2, blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 1, blockArray[3]->returnPosY() - 1);
            break;
        case 2:
            orientation = 3;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 2, blockArray[0]->returnPosY() - 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 1, blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY() + 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 1, blockArray[3]->returnPosY());
            break;
        case 3:
            orientation = 4;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 1, blockArray[0]->returnPosY() - 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 1, blockArray[2]->returnPosY() + 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX(), blockArray[3]->returnPosY() + 2);
            break;
        case 4:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 1, blockArray[0]->returnPosY());
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY() - 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 1, blockArray[2]->returnPosY()  -2);
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 2, blockArray[3]->returnPosY() - 1);
            break;
        default: break;
    }

}

void  LBlock::left(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() - 1, blockArray[x]->returnPosY());
    }
}

void LBlock::right(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() + 1, blockArray[x]->returnPosY());
    }
}


void LBlock::down(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX(), blockArray[x]->returnPosY() - 1);
    }
}

int LBlock::getPosX(int i){
    return blockArray[i]->returnPosX();
}

int LBlock::getPosY(int i){
    return blockArray[i]->returnPosY();
}

char LBlock::getType(){
    return type;
}

void LBlock::drop(){
//TODO: Kete
}

void LBlock::print(){
    for (int i = 0; i < 4; i++){
        blockArray[i]->print();
    }
}

QuadBlock* LBlock::blockFactory(){
    return new LBlock(*this);
}

