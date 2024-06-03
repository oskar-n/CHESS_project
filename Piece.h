#ifndef Piece_CLASS_H
#define Piece_CLASS_H


enum State {
	selected,
	not_selected,
	active_space
};

struct Piece {
	char color;
	char type;
	int state;
	bool has_moved;

	void set(char color, char type, State state, bool has_moved);

	
};

#endif