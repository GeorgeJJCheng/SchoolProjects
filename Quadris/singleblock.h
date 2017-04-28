#ifndef SINGLEBLOCK_H
#define SINGLEBLOCK_H
#include "posn.h"


class SingleBlock
{
    public:
        SingleBlock(int x, int y, char type);
        void print();
        void left();
        void right();
        void down();
        void setPos(int x, int y);
        int returnPosX();
        int returnPosY();
        char getChar();

    private:
        Posn myPos;
        char type;
};

#endif // SINGLEBLOCK_H
