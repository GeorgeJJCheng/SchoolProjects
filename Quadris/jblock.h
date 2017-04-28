#ifndef JBLOCK_H
#define JBLOCK_H

#include "quadblock.h"


class JBlock : public QuadBlock
{
    public:
        JBlock();
        JBlock(const JBlock &other);
        ~JBlock();
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

#endif // JBLOCK_H
