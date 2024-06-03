#include"Piece.h"

void Piece::set(char color, char type, State state, bool has_moved) {
	this->color = color;
	this->type = type;
	this->state = state;
	this->has_moved = has_moved;
}



