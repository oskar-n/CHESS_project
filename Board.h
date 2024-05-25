#ifndef BOARD_CLASS_H
#define BOARD_CLASS_H

#include "Pawn.h"
#include <GLFW/glfw3.h>


enum SelectionMovement {
	B_UP,
	B_DOWN,
	B_LEFT,
	B_RIGHT
};
struct Board {
	char turn;

	Pawn chessboard[8][8];

	Board();
	void check_coolor(int, int);
	void check_type();
	void selection_movement( SelectionMovement direction);

	
};
#endif