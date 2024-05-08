#ifndef PAWN_CLASS_H
#define PAWN_CLASS_H


struct Pawn {
	char color;
	char type;

	void set(char color, char type);

	void draw();
};

#endif