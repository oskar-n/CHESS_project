#ifndef BOARD_CLASS_H
#define BOARD_CLASS_H

#include "Pawn.h"

struct Board {
	char turn;

	Pawn chessboard[8][8];

	Board();
	void check_coolor(int, int);
	void check_type();

	
};
#endif