#include "Board.h"


Board::Board() {
	reset();
};

void Board::reset()
{

	turn = 'w';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			chessboard[i][j].set(' ', ' ', not_selected);
		}
	}
	chessboard[0][0].set('b', 'r', not_selected);
	chessboard[0][1].set('b', 'n', not_selected);
	chessboard[0][2].set('b', 'b', not_selected);
	chessboard[0][3].set('b', 'q', not_selected);
	chessboard[0][4].set('b', 'k', not_selected);
	chessboard[0][5].set('b', 'b', not_selected);
	chessboard[0][6].set('b', 'n', not_selected);
	chessboard[0][7].set('b', 'r', not_selected);
	for (int i = 0; i < 8; i++)
	{
		chessboard[1][i].set('b', 'p', not_selected);
	}

	chessboard[7][0].set('w', 'r', not_selected);
	chessboard[7][1].set('w', 'n', not_selected);
	chessboard[7][2].set('w', 'b', not_selected);
	chessboard[7][3].set('w', 'q', not_selected);
	chessboard[7][4].set('w', 'k', not_selected);
	chessboard[7][5].set('w', 'b', not_selected);
	chessboard[7][6].set('w', 'n', not_selected);
	chessboard[7][7].set('w', 'r', not_selected);

	for (int i = 0; i < 8; i++)
	{
		chessboard[6][i].set('w', 'p', not_selected);
	}

	memory.clear();
}

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
	if (direction == B_DOWN)
	{
		if (highlight_box.x < 7)
		{
			highlight_box.x++;
		}
	}
	else if (direction == B_UP)
	{
		if (highlight_box.x > 0)
		{
			highlight_box.x--;
		}
	}
	else if (direction == B_LEFT)
	{
		if (highlight_box.y > 0)
		{
			highlight_box.y--;
		}
	}
	else if (direction == B_RIGHT)
	{
		if (highlight_box.y < 7)
		{
			highlight_box.y++;
		}
	}
	
}



void Board::select_piece()
{
	if (chessboard[highlight_box.x][highlight_box.y].state == not_selected && memory.last_piece.type == ' ')
	{
		if(chessboard[highlight_box.x][highlight_box.y].color == turn)
		{

			chessboard[highlight_box.x][highlight_box.y].state = selected;
			memory.last_piece = chessboard[highlight_box.x][highlight_box.y];
			memory.x = highlight_box.x;
			memory.y = highlight_box.y;
		}
	}
	
	
}

void Board::move_piece()
{
	
		if (chessboard[highlight_box.x][highlight_box.y].state == selected && memory.last_piece.type != ' ')
		{
			if(!(highlight_box.x == memory.x && highlight_box.y == memory.y) && chessboard[highlight_box.x][highlight_box.y].color != turn)
			{
				chessboard[highlight_box.x][highlight_box.y] = memory.last_piece;
				chessboard[memory.x][memory.y].set(' ', ' ', not_selected);
				memory.clear();
				clear_selection();
				turn = (turn == 'w') ? 'b' : 'w';
			}
		}
	
}
void Board::piece_movement()
{


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chessboard[i][j].state == selected)
			{
				if (chessboard[i][j].color == 'b' && i < 7 && chessboard[i + 1][j].color != 'b')
				{
					chessboard[i + 1][j].state = selected;
				}
				else if (chessboard[i][j].color == 'w' && i > 0 && chessboard[i-1][j].color != 'w')
				{
					chessboard[i - 1][j].state = selected;
				}
			}

			


		}
	}
}

void Board::clear_selection()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chessboard[i][j].state == selected)
			{
				chessboard[i][j].state = not_selected;
			}
		}
	}
	memory.clear();
}
