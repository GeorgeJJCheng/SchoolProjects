#include "zblock.h"

ZBlock::ZBlock():type('Z'),orientation(1){
    blockArray[0] = new SingleBlock(0,14,type);
    blockArray[1] = new SingleBlock(1,14,type);
    blockArray[2] = new SingleBlock(1,13,type);
    blockArray[3] = new SingleBlock(2,13,type);
}

ZBlock::ZBlock(const ZBlock &other){
    type = other.type;
    orientation = other.orientation;
    for (int i = 0; i < 4; i++){
        blockArray[i] = new SingleBlock(other.blockArray[i]->returnPosX(),other.blockArray[i]->returnPosY(),type);
    }
}

ZBlock::~ZBlock(){
    for (int i = 0; i < 4; i++){
        delete blockArray[i];
    }
}

void ZBlock::ccRotate(){
    this -> cRotate();

}

void ZBlock::cRotate(){

     switch(orientation){

        case 1:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 1, blockArray[0]->returnPosY() + 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 1, blockArray[2]->returnPosY() + 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 2, blockArray[3]->returnPosY());
            break;
        case 2:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 1, blockArray[0]->returnPosY() - 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 1, blockArray[2]->returnPosY() - 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 2, blockArray[3]->returnPosY());
            break;
        default: break;
    }

}

void  ZBlock::left(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() - 1, blockArray[x]->returnPosY());
    }
}

void ZBlock::right(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() + 1, blockArray[x]->returnPosY());
    }
}


void ZBlock::down(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX(), blockArray[x]->returnPosY() - 1);
    }
}

void ZBlock::drop(){
//TODO:KETE
}

int ZBlock::getPosX(int i){
    return blockArray[i]->returnPosX();
}

int ZBlock::getPosY(int i){
    return blockArray[i]->returnPosY();new SingleBlock(1,14,type);
}
char ZBlock::getType(){
    return type;
}

void ZBlock::print(){
    for (int i = 0; i < 4; i++){
        blockArray[i]->print();
    }
}

QuadBlock* ZBlock::blockFactory(){
    return new ZBlock(*this);
}


