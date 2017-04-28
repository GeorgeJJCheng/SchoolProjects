#ifndef POSN_H
#define POSN_H


class Posn
{
    public:
        Posn(int x, int y);
        int getX();
        int getY();
        void setX(int x);
        void setY(int y);

    private:
        int xPos;
        int yPos;
};

#endif // POSN_H
