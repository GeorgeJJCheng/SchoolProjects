#include "jblock.h"

JBlock::JBlock():type('J'),orientation(1){
    blockArray[0] = new SingleBlock(0,14,type);
    blockArray[1] = new SingleBlock(0,13,type);
    blockArray[2] = new SingleBlock(1,13,type);
    blockArray[3] = new SingleBlock(2,13,type);
}

JBlock::JBlock(const JBlock &other ){
    type = other.type;
    orientation = other.orientation;
    for (int i = 0; i < 4; i++){
        blockArray[i] = new SingleBlock(other.blockArray[i]->returnPosX(),other.blockArray[i]->returnPosY(),type);
    }
}

JBlock::~JBlock(){
    for (int i = 0; i < 4; i++){
        delete blockArray[i];
    }
}

void JBlock::ccRotate(){
    switch(orientation){

        case 1:
            orientation = 4;
                blockArray[0]->setPos(blockArray[0]->returnPosX(), blockArray[0]->returnPosY() - 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 1, blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY() + 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 1, blockArray[3]->returnPosY() + 2);
            break;
        case 2:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 1, blockArray[0]->returnPosY() - 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY() - 2);
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 1, blockArray[2]->returnPosY() - 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 2, blockArray[3]->returnPosY());
            break;
        case 3:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 1, blockArray[0]->returnPosY() + 2);
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 2, blockArray[1]->returnPosY() + 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 1, blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX(), blockArray[3]->returnPosY() - 1);
            break;
        case 4:
            orientation = 3;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 2, blockArray[0]->returnPosY());
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 1, blockArray[1]->returnPosY() + 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 1, blockArray[3]->returnPosY() - 1);
            break;
        default: break;
    }

}

void JBlock::cRotate(){

     switch(orientation){

        case 1:
            orientation = 2;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 1, blockArray[0]->returnPosY() + 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX(), blockArray[1]->returnPosY() + 2);
            blockArray[2]->setPos(blockArray[2]->returnPosX() - 1, blockArray[2]->returnPosY() + 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() - 2, blockArray[3]->returnPosY());
            break;
        case 2:
            orientation = 3;
            blockArray[0]->setPos(blockArray[0]->returnPosX() + 1, blockArray[0]->returnPosY() - 2);
            blockArray[1]->setPos(blockArray[1]->returnPosX() + 2, blockArray[1]->returnPosY() - 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX() + 1, blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX(), blockArray[3]->returnPosY() + 1);
            break;
        case 3:
            orientation = 4;
            blockArray[0]->setPos(blockArray[0]->returnPosX() - 2, blockArray[0]->returnPosY());
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 1, blockArray[1]->returnPosY() - 1);
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY());
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 1, blockArray[3]->returnPosY() + 1);
            break;
        case 4:
            orientation = 1;
            blockArray[0]->setPos(blockArray[0]->returnPosX(), blockArray[0]->returnPosY() + 1);
            blockArray[1]->setPos(blockArray[1]->returnPosX() - 1, blockArray[1]->returnPosY());
            blockArray[2]->setPos(blockArray[2]->returnPosX(), blockArray[2]->returnPosY() - 1);
            blockArray[3]->setPos(blockArray[3]->returnPosX() + 1, blockArray[3]->returnPosY() -2);
            break;
        default: break;
    }

}

void  JBlock::left(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() - 1, blockArray[x]->returnPosY());
    }
}

void JBlock::right(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX() + 1, blockArray[x]->returnPosY());
    }
}


void JBlock::down(){
    for (int x = 0; x < 4; x++){
        blockArray[x]->setPos(blockArray[x]->returnPosX(), blockArray[x]->returnPosY() - 1);
    }
}

int JBlock::getPosX(int i){
    return blockArray[i]->returnPosX();
}

int JBlock::getPosY(int i){
    return blockArray[i]->returnPosY();
}

char JBlock::getType(){
    return type;
}

void JBlock::drop(){
//TODO: Kete
}

void JBlock::print(){
    for (int i = 0; i < 4; i++){
        blockArray[i]->print();
    }
}

QuadBlock* JBlock::blockFactory(){
    return new JBlock(*this);
}

