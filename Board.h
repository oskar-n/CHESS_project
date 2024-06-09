#ifndef BOARD_CLASS_H
#define BOARD_CLASS_H

#include "Piece.h"
#include "Highlight_box.h"
#include <GLFW/glfw3.h>


enum SelectionMovement {
	B_UP,
	B_DOWN,
	B_LEFT,
	B_RIGHT
};

struct Memory {
	Piece last_piece;
	int x;
	int y;

	void clear()
	{
		last_piece.set(' ', ' ', not_selected, false);
		x = NULL;
		y = NULL;
	}
};


struct Board {
	char turn;

	Piece chessboard[8][8];
	Highlight_box highlight_box;

	Memory memory;

	Board();
	void reset();
	void check_coolor(int, int);
	void check_type();
	void selection_movement( SelectionMovement direction);
	void select_piece();
	void move_piece();
	void piece_movement();
	void clear_selection();
	bool is_white_in_check();
	bool is_black_in_check();
	

	
};
#endif