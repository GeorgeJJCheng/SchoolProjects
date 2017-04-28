#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "quadblock.h"


class ZBlock : public QuadBlock
{
    public:
        ZBlock();
        ZBlock(const ZBlock &other);
        ~ZBlock();
        void down();
        void left();
        void right();
        void drop();
        void print();
        void ccRotate();
        void cRotate();
        int getPosX(int i);
        int getPosY(int i);
        char getType();
        QuadBlock* blockFactory();
    private:
        //Type of block represented by char
        char type;
        //Rotation state of block (0-3)
        int orientation;
        //Array of blocks that make up the state
        SingleBlock *blockArray[4];
};

#endif // ZBLOCK_H
