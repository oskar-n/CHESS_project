#ifndef PAWN_CLASS_H
#define PAWN_CLASS_H


struct Pawn {
	char color;
	char type;
	bool is_selected;

	void set(char color, char type, bool select);

	void draw();
};

#endif