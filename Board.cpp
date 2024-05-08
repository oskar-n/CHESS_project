#include "Board.h"


Board::Board() {

	turn = 'w';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			chessboard[i][j].set(' ', ' ');
		}
	}	
	chessboard[0][0].set('b', 'r');
	chessboard[0][1].set('b', 'n');
	chessboard[0][2].set('b', 'b');
	chessboard[0][3].set('b', 'q');
	chessboard[0][4].set('b', 'k');
	chessboard[0][5].set('b', 'b');
	chessboard[0][6].set('b', 'n');
	chessboard[0][7].set('b', 'r');
	for (int i = 0; i < 8; i++)
	{
		chessboard[1][i].set('b', 'p');
	}	

	chessboard[7][0].set('w', 'r');
	chessboard[7][1].set('w', 'n');
	chessboard[7][2].set('w', 'b');
	chessboard[7][3].set('w', 'q');
	chessboard[7][4].set('w', 'k');
	chessboard[7][5].set('w', 'b');
	chessboard[7][6].set('w', 'n');
	chessboard[7][7].set('w', 'r');

	for (int i = 0; i < 8; i++)
	{
		chessboard[6][i].set('w', 'p');
	}
};

void  Board::check_coolor(int posx, int posy)
{
	if (chessboard[posx][posy].color == 'w')
	{
		turn = 'b';
	}
	else
	{
		turn = 'w';
	}
}
