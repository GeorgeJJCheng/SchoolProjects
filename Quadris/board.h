#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include "quadblock.h"
#include "singleblock.h"
#include "iblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "oblock.h"
#include "lblock.h"
#include "jblock.h"
#include "window.h"

class Board {
	public:
	  Board();
	  ~Board();
	  bool cClock();
	  bool clock();
	  void bLeft();
	  void bRight();
	  void bDown();
	  void clearBoard();
	  void clearRow();
	  int checkState(int diff);
	  void printRow(int row, bool graphics, Xwindow* w);
	  void printBoard(bool graphics, Xwindow* w);
	  void blockToChar();
	  void getHint();
	  void setActive(std::string s);
	  bool checkLeft();
	  bool checkRight();
	  bool checkDown();
	  void dropstar(int i);
	  void setNextBlock(char c);
	  char getNextBlock();
	  void setNewActive(std::string type);
	  void updateHeight();
	  int getScore();
	  int returnInd(int i);
	private:
	  void clearRow(int row);
	  SingleBlock* state[18][11];
	  int topIndex[11];
	  QuadBlock* activeBlock;
	  QuadBlock* hintBlock;
	  char nextBlock;
	  int hint;
	  bool gravity;
	  int starblocks;
	  int score;
};

#endif
