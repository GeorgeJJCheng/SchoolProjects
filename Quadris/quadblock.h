#ifndef QUADBLOCK_H
#define QUADBLOCK_H
#include "singleblock.h"

class QuadBlock
{
    public:
        QuadBlock();
        virtual ~QuadBlock();
        virtual void left();
        virtual void right();
        virtual void down();
        virtual void drop();
        virtual void print();
        virtual void cRotate();
        virtual void ccRotate();
        virtual int getPosX(int i);
        virtual int getPosY(int i);
        virtual char getType();
        virtual QuadBlock* blockFactory();

    private:
        //Type of block represented by char
        char type;
        //Rotation state of block (0-3)
        int orientation;
        //Array of blocks that make up the state
        SingleBlock *blockArray[4];
};


#endif // QUADBLOCK_H
