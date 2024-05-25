#include "Board.h"


Board::Board() {

	turn = 'w';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			chessboard[i][j].set(' ', ' ', 0);
		}
	}	
	chessboard[0][0].set('b', 'r', 0);
	chessboard[0][1].set('b', 'n', 0);
	chessboard[0][2].set('b', 'b', 0);
	chessboard[0][3].set('b', 'q', 0);
	chessboard[0][4].set('b', 'k', 0);
	chessboard[0][5].set('b', 'b', 0);
	chessboard[0][6].set('b', 'n', 0);
	chessboard[0][7].set('b', 'r', 0);
	for (int i = 0; i < 8; i++)
	{
		chessboard[1][i].set('b', 'p', 0);
	}	

	chessboard[7][0].set('w', 'r', 0);
	chessboard[7][1].set('w', 'n', 0);
	chessboard[7][2].set('w', 'b', 0);
	chessboard[7][3].set('w', 'q', 0);
	chessboard[7][4].set('w', 'k', 1);
	chessboard[7][5].set('w', 'b', 0);
	chessboard[7][6].set('w', 'n', 0);
	chessboard[7][7].set('w', 'r', 0);

	for (int i = 0; i < 8; i++)
	{
		chessboard[6][i].set('w', 'p', 0);
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

void Board::selection_movement(SelectionMovement direction)
{

	bool stop = 0; // 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			chessboard[i][j].is_selected == 1;


			if (direction == B_UP && i > 0)
			{
				chessboard[i][j].is_selected = 0;
				chessboard[i - 1][j].is_selected = 1;
				stop =1;
			}
			else if (direction == B_DOWN && i < 7)
			{
				chessboard[i][j].is_selected = 0;
				chessboard[i + 1][j].is_selected = 1;
				stop = 1;
			}
			else if (direction == B_LEFT && j > 0)
			{
				chessboard[i][j].is_selected = 0;
				chessboard[i][j-1].is_selected = 1;
				stop = 1;
			}
			else if (direction == B_RIGHT && j < 7)
			{
				chessboard[i][j].is_selected = 0;
				chessboard[i][j+1].is_selected = 1;
				stop = 1;
			}
			if (stop == 1)
			{
				break;
			}
				
		}
		if (stop == 1)
		{
			break;
		}
	}
	stop = 0;
}
