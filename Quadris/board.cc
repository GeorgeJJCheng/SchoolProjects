#include "board.h"
#include <iostream>

using namespace std;

Board::Board(): nextBlock('x'), hint(0), gravity(false), starblocks(0), score(0) {
	for (int i=0; i<11; i++) {
		for (int j=0; j<18; j++) {
			state[j][i]=nullptr;
		}
		topIndex[i]=-1;
	}
	activeBlock = new IBlock();
	hintBlock=nullptr;
}

Board::~Board() {
	for (int i=0; i<11; i++) {
		for (int j=0; j<18; j++) {
			if (state[j][i]!=nullptr) {
				delete state[j][i];
			}
		}
	}
	if (activeBlock!=nullptr)
    {
        delete activeBlock;
    }
	if (hintBlock!=nullptr) {
		delete hintBlock;
	}
}

int Board::getScore()
{
    return score;
}

void Board::updateHeight() {
	for (int i=0; i<11; i++) {
		for (int j=14; j>=0; j--) {
			if (state[j][i]!=nullptr) {
				topIndex[i]=j;
				break;
			}
			topIndex[i] = -1;
		}
	}
}

void Board::setNewActive(string type) {
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		delete state[y][x];
		state[y][x]=nullptr;
	}
	delete activeBlock;
	setActive(type);
}

void Board::setNextBlock(char c) {
	nextBlock=c;
}

char Board::getNextBlock() {
	return nextBlock;
}

bool Board::cClock() {
	bool q=true;
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		delete state[y][x];
		state[y][x]=nullptr;
	}
	activeBlock->ccRotate();
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		if (state[y][x]!=nullptr) {
			activeBlock->cRotate();
			q=false;
			break;
		}
	}
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		char c=activeBlock->getType();
		SingleBlock* s= new SingleBlock(x,y,c);
		state[y][x]=s;
	}
	return q;
}

bool Board::clock() {
	bool q=true;
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		delete state[y][x];
		state[y][x]=nullptr;
	}
	activeBlock->cRotate();
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		if (state[y][x]!=nullptr) {
			activeBlock->ccRotate();
			q=false;
			break;
		}
	}
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		char c=activeBlock->getType();
		SingleBlock* s= new SingleBlock(x,y,c);
		state[y][x]=s;
	}
	return q;
}

void Board::bLeft() {
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		delete state[y][x];
		state[y][x]=nullptr;
	}
	activeBlock->left();
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		char c=activeBlock->getType();
		SingleBlock* s= new SingleBlock(x,y,c);
		state[y][x]=s;
	}
}

void Board::bRight() {
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		delete state[y][x];
		state[y][x]=nullptr;
	}
	activeBlock->right();
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		char c=activeBlock->getType();
		SingleBlock* s= new SingleBlock(x,y,c);
		state[y][x]=s;
	}
}

void Board::bDown() {
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		delete state[y][x];
		state[y][x]=nullptr;
	}
	activeBlock->down();
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		char c=activeBlock->getType();
		SingleBlock* s= new SingleBlock(x,y,c);
		state[y][x]=s;
	}
}

void Board::clearBoard() {
	for (int i=0; i<11; i++) {
		for (int j=0; j<18; j++) {
			delete state[j][i];
			state[j][i]=nullptr;
		}
		topIndex[i]=-1;
	}
	starblocks = 0;
}

void Board::dropstar(int i) {
	if (i==4) {
		if (starblocks==5) {
            bool hasDropped = false;
			for (int m = 15; m > -1; m--)
			{
				if (state[m][5] != nullptr)
				{
					state[m+1][5] = new SingleBlock(5, m+1, '*');
					updateHeight();
                    hasDropped = true;
					break;
				}
			}
			if (!hasDropped)
            {
                state[0][5] = new SingleBlock(5, 0, '*');
            }
			starblocks = 0;
		}
	}
	else {
		starblocks=0;
	}
}

void Board::clearRow(int row) {
	for (int i=0; i<11; i++) {
		delete state[row][i];
		state[row][i]=state[row+1][i];
	}
	for (int i=row+1; i<15; i++) {
		for (int j=0; j<11; j++) {
			state[i][j]=state[i+1][j];
		}
	}
	score += 100;
	starblocks=0;
}

int Board::checkState(int diff) {
	int result = 0;
	int bonusPoints = 0;
	if (checkDown())
    {
        result = 1;
        starblocks++;
        dropstar(diff);
        for (int i = 15; i > -1 ; i--)
        {
            int blocksInRow = 0;
            for (int j = 0; j < 11; j++)
            {
                if (state[i][j] != nullptr)
                {
                    blocksInRow++;
                }
            }
            if (blocksInRow == 11)
            {
                clearRow(i);
                score += bonusPoints;
                bonusPoints += 100;
            }
            blocksInRow = 0;
        }
    }
	if (hint == 2) {
		hint--;
	}
	else if (hint == 1) {
		hint--;
		for (int i=0; i<4; i++) {
			int col=hintBlock->getPosX(i);
			int row=hintBlock->getPosY(i);
			state[row][col]=nullptr;
			//delete hintBlock->blockarray[i];
		}
		delete hintBlock;
	}
    return result;
}

void Board::printRow(int row, bool graphics, Xwindow* w) {
	cout << "|";
	for (int i=0; i<11; i++) {
		if (state[row][i] == nullptr) {
			cout << " ";
		}
		else {
			state[row][i]->print();
		}
		if (graphics==true && state[row][i]!=nullptr) {
			char c=state[row][i]->getChar();
			if (c=='I') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Cyan); //360 is first block
			}
			else if (c=='S') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Blue);
			}
			else if (c=='Z') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Green);
			}
			else if (c=='L') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Yellow);
			}
			else if (c=='J') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Orange);
			}
			else if (c=='T') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Magenta);
			}
			else if (c=='O') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Brown);
			}
			else if (c=='*') {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Red);
			}
			else {
				w->fillRectangle((i*20)+30,(row*-20)+400,20,20,Xwindow::Black);
			}
		}
		else if (graphics==true) {
			w->fillRectangle((i*20)+30, (row*-20)+400,20,20,Xwindow::White);
		}
		cout << "|";
	}
	cout << endl;
}

void Board::printBoard(bool graphics, Xwindow* w) {
//	w.fillRectangle(x,y,width,height,colour Xwindow::red)
//	w.drawString(x,y,string)
	if (graphics==true) {
		w->drawString(30,10,"Level:");
		w->drawString(30,20,"Score:");
		w->drawString(30,30,"Hi Score");
	}
	cout << "|-|-|-|-|-|-|-|-|-|-|-|" << endl;
	for (int i=17; i>=0; i--) {
		printRow(i,graphics,w);
	}
	if (graphics==true) {
		for (int i=0; i<19; i++) {
			w->fillRectangle(30,(i*20)+59,220,1,Xwindow::Black);
		}
		for (int i=0; i<12; i++) {
			w->fillRectangle((i*20)+29,60,1,360,Xwindow::Black);
		}
	}
	cout << "|-|-|-|-|-|-|-|-|-|-|-|" << endl;
	cout << "Next: " << endl;
	if (graphics==true) {
		w->drawString(30, 430, "Next:");
		w->fillRectangle(30, 440, 80, 40, Xwindow::White);
	}
	if (nextBlock == 'l') {
		cout << "  L" << endl << "LLL" << endl;
		if (graphics==true) {
			w->fillRectangle(70,440,20,20,Xwindow::Yellow);
			w->fillRectangle(30,460,60,20,Xwindow::Yellow);
		}
	}
	else if (nextBlock == 'j') {
		cout << "J  " << endl << "JJJ" << endl;
		if (graphics==true) {
			w->fillRectangle(30,440,20,20,Xwindow::Orange);
			w->fillRectangle(30,460,60,20,Xwindow::Orange);
		}
	}
	else if (nextBlock == 's') {
		cout << " SS" << endl << "SS" << endl;
		if (graphics==true) {
			w->fillRectangle(50,440,40,20,Xwindow::Blue);
			w->fillRectangle(30,460,40,20,Xwindow::Blue);
		}
	}
	else if (nextBlock == 'z') {
		cout << "ZZ" << endl << " ZZ" << endl;
		if (graphics==true) {
			w->fillRectangle(30,440,40,20,Xwindow::Green);
			w->fillRectangle(50,460,40,20,Xwindow::Green);
		}
	}
	else if (nextBlock == 'o') {
		cout << "OO" << endl << "OO" << endl;
		if (graphics==true) {
			w->fillRectangle(30,440,40,20,Xwindow::Brown);
			w->fillRectangle(30,460,40,20,Xwindow::Brown);
		}
	}
	else if (nextBlock == 't') {
		cout << "TTT" << endl << " T" << endl;
		if (graphics==true) {
			w->fillRectangle(30,440,60,20,Xwindow::Magenta);
			w->fillRectangle(50,460,20,20,Xwindow::Magenta);
		}
	}
	else {
		cout << "IIII" << endl;
		if (graphics==true) {
			w->fillRectangle(30,440,80,20,Xwindow::Cyan);
		}
	}
}

void Board::getHint() {
	int low=18;
	int moves=-11;
	int farleft=12;
	int leftmoves=0;
	int rightmoves=0;
	int touch=0;
	int currleft=0;
	hintBlock=activeBlock->blockFactory();
	while(checkRight()==false) {
		hintBlock->right();
		rightmoves++;
	}
	while(checkLeft()==false) {
		hintBlock->left();
		leftmoves++;
	}
	leftmoves=leftmoves-rightmoves-1;
	for (int j=0; j<4; j++) {
		if (farleft>hintBlock->getPosX(j)) {
			farleft=hintBlock->getPosX(j);
		}
	}
	while(checkDown()==false) {
		hintBlock->down();
	}
	int currtouch=0;
	int currlow=18;
	for (int j=0; j<4; j++) {
		int x=hintBlock->getPosX(j);
		int y=hintBlock->getPosY(j);
		if (state[y][x-1]!=nullptr) {
			currtouch++;
		}
		if (y<currlow) {
			currlow=y;
		}
	}
	moves=leftmoves+1;
	low=currlow;
	touch=currtouch;
	for (int i=leftmoves; i>0; i--) {
		currtouch=0;
		currlow=18;
		currleft=0;
		delete hintBlock;
		hintBlock=activeBlock->blockFactory();
		for (int j=0; j<leftmoves; j++) {
			hintBlock->left();
			currleft++;
		}
		while (checkDown()==false) {
			hintBlock->down();
		}
		for (int j=0; j<4; j++) {
			int x=hintBlock->getPosX(j);
			int y=hintBlock->getPosY(j);
			if (state[y][x-1]!=nullptr) {
				currtouch++;
			}
			if (y<currlow) {
				currlow=y;
			}
		}
		if (currtouch==touch && currlow==low && moves<currleft) {
			moves=currleft;
		}
		else if (currtouch==touch && currlow>low) {
			low=currlow;
		}
		else if (currtouch>touch) {
			touch=currtouch;
			low=currlow;
			moves=currleft;
		}
	}
	for (int i=rightmoves; i>0; i--) {
		currtouch=0;
		currlow=18;
		currleft=0;
		delete hintBlock;
		hintBlock=activeBlock->blockFactory();
		for (int j=0; j<rightmoves; j++) {
			hintBlock->right();
			currleft--;
		}
		while (checkDown()==false) {
			hintBlock->down();
		}
		for (int j=0; j<4; j++) {
			int x=hintBlock->getPosX(j);
			int y=hintBlock->getPosY(j);
			if (x<currleft) {
				currleft=x;
			}
			if (state[y][x-1]!=nullptr) {
				currtouch++;
			}
			if (y<currlow) {
				currlow=y;
			}
		}
		if (currtouch==touch && currlow==low && moves<currleft) {
			moves=currleft;
		}
		else if (currtouch==touch && currlow>low) {
			low=currlow;
		}
		else if (currtouch>touch) {
			touch=currtouch;
			low=currlow;
			moves=currleft;
		}
	}
	delete hintBlock;
	hintBlock=activeBlock->blockFactory();
	if (moves<0) {
		for (; moves!=0; moves++) {
			hintBlock->right();
		}
	}
	if (moves>0) {
		for (; moves!=0; moves++) {
			hintBlock->left();
		}
	}
	while (checkDown()==false) {
		hintBlock->down();
	}
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		SingleBlock* s= new SingleBlock(x,y,'?');
		state[y][x]=s;
	}
	hint=2;
}

int Board::returnInd(int i)
{
    return topIndex[i];
}

void Board::setActive(string s) {
    delete activeBlock;
	if (s=="S") {
		activeBlock= new SBlock();
	}
	else if (s=="Z") {
		activeBlock= new ZBlock();
	}
	else if (s=="J") {
		activeBlock= new JBlock();
	}
	else if (s=="L") {
		activeBlock= new LBlock();
	}
	else if (s=="I") {
		activeBlock= new IBlock();
	}
	else if (s=="O") {
		activeBlock= new OBlock();
	}
	else {
		activeBlock= new TBlock();
	}
	for (int i=0; i<4; i++) {
		int x=activeBlock->getPosX(i);
		int y=activeBlock->getPosY(i);
		char c=activeBlock->getType();
		state[y][x]=new SingleBlock(x,y,c);
	}
}

bool Board::checkLeft()
{
    bool collision = false;
    for (int i = 0; i < 4; i++)
    {
        int x = activeBlock->getPosX(i);
        int y = activeBlock->getPosY(i);
		for (int j=0; j<4; j++) {
	        int b = activeBlock->getPosX(j);
    	    int a = activeBlock->getPosY(j);
        	delete state[a][b];
        	state[a][b] = nullptr;
		}
        if (x - 1 < 0 || state[y][x-1] != nullptr)
        {
            collision = true;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int x=activeBlock->getPosX(i);
        int y=activeBlock->getPosY(i);
        char c=activeBlock->getType();
        SingleBlock* s= new SingleBlock(x,y,c);
        state[y][x]=s;
    }
    return collision;
}
bool Board::checkRight()
{
    bool collision = false;
    for (int i = 0; i < 4; i++)
    {
        int x = activeBlock->getPosX(i);
        int y = activeBlock->getPosY(i);
		for (int j=0; j<4; j++) {
	        int b = activeBlock->getPosX(j);
    	    int a = activeBlock->getPosY(j);
        	delete state[a][b];
        	state[a][b] = nullptr;
		}
        if (x + 1 > 10 || state[y][x+1] != nullptr)
        {
            collision = true;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int x=activeBlock->getPosX(i);
        int y=activeBlock->getPosY(i);
        char c=activeBlock->getType();
        SingleBlock* s= new SingleBlock(x,y,c);
        state[y][x]=s;
    }
    return collision;
}
bool Board::checkDown()
{
    bool collision = false;
    for (int i = 0; i < 4; i++)
    {
        int x = activeBlock->getPosX(i);
        int y = activeBlock->getPosY(i);
		for (int j=0; j<4; j++) {
	        int b = activeBlock->getPosX(j);
    	    int a = activeBlock->getPosY(j);
        	delete state[a][b];
        	state[a][b] = nullptr;
		}
        if (y - 1 < 0 || state[y-1][x] != nullptr)
        {
            collision = true;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int x=activeBlock->getPosX(i);
        int y=activeBlock->getPosY(i);
        char c=activeBlock->getType();
        SingleBlock* s= new SingleBlock(x,y,c);
        state[y][x]=s;
    }
    return collision;
}
