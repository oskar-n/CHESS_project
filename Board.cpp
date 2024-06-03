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
			chessboard[i][j].set(' ', ' ', not_selected, false);
		}
	}
	chessboard[0][0].set('b', 'r', not_selected, false);
	chessboard[0][1].set('b', 'n', not_selected, false);
	chessboard[0][2].set('b', 'b', not_selected, false);
	chessboard[0][3].set('b', 'q', not_selected, false);
	chessboard[0][4].set('b', 'k', not_selected, false);
	chessboard[0][5].set('b', 'b', not_selected, false);
	chessboard[0][6].set('b', 'n', not_selected, false);
	chessboard[0][7].set('b', 'r', not_selected, false);
	for (int i = 0; i < 8; i++)
	{
		chessboard[1][i].set('b', 'p', not_selected, false);
	}

	chessboard[7][0].set('w', 'r', not_selected, false);
	chessboard[7][1].set('w', 'n', not_selected, false);
	chessboard[7][2].set('w', 'b', not_selected, false);
	chessboard[7][3].set('w', 'q', not_selected, false);
	chessboard[7][4].set('w', 'k', not_selected, false);
	chessboard[7][5].set('w', 'b', not_selected, false);
	chessboard[7][6].set('w', 'n', not_selected, false);
	chessboard[7][7].set('w', 'r', not_selected, false);

	for (int i = 0; i < 8; i++)
	{
		chessboard[6][i].set('w', 'p', not_selected, false);
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
				chessboard[highlight_box.x][highlight_box.y].has_moved = true;
				chessboard[memory.x][memory.y].set(' ', ' ', not_selected, false);
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
				//Black pieces

				if (chessboard[i][j].color == 'b'  && turn == 'b')//memory last piece used to deactivate selected squares from other pieces
				{
					if (chessboard[i][j].type == 'p' && memory.last_piece.type == 'p' && i + 1 < 8) //movement of the black pawn
					{
						chessboard[i + 1][j].state = (chessboard[i + 1][j].color == 'b' || chessboard[i+ 1][j].color == 'w') ? not_selected : selected;
						if (chessboard[i+2][j].color == ' ' && i + 2 < 8 && chessboard[i][j].has_moved == false)
						{
							chessboard[i+2][j].state = selected;
						}

						if (chessboard[i + 1][j - 1].color == 'w' && j - 1 >= 0)
						{
							chessboard[i + 1][j - 1].state = selected;
						}
						if (chessboard[i + 1][j + 1].color == 'w' && j + 1 < 8)
						{
							chessboard[i + 1][j + 1].state = selected;
						}

					}
					else if (chessboard[i][j].type == 'b' && memory.last_piece.type == 'b') //moves of the black bishop
					{
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j + temp_i < 8)
							{
								if (chessboard[i + temp_i][j + temp_i].color == 'b') break;
								chessboard[i + temp_i][j + temp_i].state = selected;
								if (chessboard[i + temp_i][j + temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j - temp_i >= 0)
							{
								if (chessboard[i + temp_i][j - temp_i].color == 'b') break;
								chessboard[i + temp_i][j - temp_i].state = selected;
								if (chessboard[i + temp_i][j - temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j + temp_i < 8)
							{
								if (chessboard[i - temp_i][j + temp_i].color == 'b') break;
								chessboard[i - temp_i][j + temp_i].state = selected;
								if (chessboard[i - temp_i][j + temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j - temp_i].color == 'b') break;
								chessboard[i - temp_i][j - temp_i].state = selected;
								if (chessboard[i - temp_i][j - temp_i].color == 'w') break;

							}
						}

					}
					else if (chessboard[i][j].type == 'r' && memory.last_piece.type == 'r') //movement of the black rook
					{
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8)
							{
								if (chessboard[i + temp_i][j].color == 'b') break;
								chessboard[i + temp_i][j].state = selected;
								if (chessboard[i + temp_i][j].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j].color == 'b') break;
								chessboard[i - temp_i][j].state = selected;
								if (chessboard[i - temp_i][j].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j + temp_i < 8)
							{
								if (chessboard[i][j + temp_i].color == 'b') break;
								chessboard[i][j + temp_i].state = selected;
								if (chessboard[i][j + temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j - temp_i >= 0)
							{
								if (chessboard[i][j - temp_i].color == 'b') break;
								chessboard[i][j - temp_i].state = selected;
								if (chessboard[i][j - temp_i].color == 'w') break;
							}
						}

					}
					else if (chessboard[i][j].type == 'k' && memory.last_piece.type == 'k')//movement of the black king
					{
						if (i - 1 >= 0)
						{
							chessboard[i - 1][j].state = (chessboard[i - 1][j].color == 'b') ? not_selected : selected;
							if (j - 1 >= 0)
							{
								chessboard[i - 1][j - 1].state = (chessboard[i - 1][j - 1].color == 'b') ? not_selected : selected;
							}
						}
						if (i + 1 < 8)
						{
							chessboard[i + 1][j].state = (chessboard[i + 1][j].color == 'b') ? not_selected : selected;
							if (j + 1 < 8)
							{
								chessboard[i + 1][j + 1].state = (chessboard[i + 1][j + 1].color == 'b') ? not_selected : selected;
							}
						}
						if (j - 1 >= 0)
						{
							chessboard[i][j - 1].state = (chessboard[i][j - 1].color == 'b') ? not_selected : selected;
							if (i + 1 < 8)
							{
								chessboard[i + 1][j - 1].state = (chessboard[i + 1][j - 1].color == 'b') ? not_selected : selected;
							}
						}
						if (j + 1 < 8)
						{
							chessboard[i][j + 1].state = (chessboard[i][j + 1].color == 'b') ? not_selected : selected;
							if (i - 1 >= 0)
							{
								chessboard[i - 1][j + 1].state = (chessboard[i - 1][j + 1].color == 'b') ? not_selected : selected;
							}
						}

					}
					else if (chessboard[i][j].type == 'q' && memory.last_piece.type == 'q') //movement of the black queen
					{
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j + temp_i < 8)
							{
								if (chessboard[i + temp_i][j + temp_i].color == 'b') break;
								chessboard[i + temp_i][j + temp_i].state = selected;
								if (chessboard[i + temp_i][j + temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j - temp_i >= 0)
							{
								if (chessboard[i + temp_i][j - temp_i].color == 'b') break;
								chessboard[i + temp_i][j - temp_i].state = selected;
								if (chessboard[i + temp_i][j - temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j + temp_i < 8)
							{
								if (chessboard[i - temp_i][j + temp_i].color == 'b') break;
								chessboard[i - temp_i][j + temp_i].state = selected;
								if (chessboard[i - temp_i][j + temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j - temp_i].color == 'b') break;
								chessboard[i - temp_i][j - temp_i].state = selected;
								if (chessboard[i - temp_i][j - temp_i].color == 'w') break;
							}
						}

						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8)
							{
								if (chessboard[i + temp_i][j].color == 'b') break;
								chessboard[i + temp_i][j].state = selected;
								if (chessboard[i + temp_i][j].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j].color == 'b') break;
								chessboard[i - temp_i][j].state = selected;
								if (chessboard[i - temp_i][j].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j + temp_i < 8)
							{
								if (chessboard[i][j + temp_i].color == 'b') break;
								chessboard[i][j + temp_i].state = selected;
								if (chessboard[i][j + temp_i].color == 'w') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j - temp_i >= 0)
							{
								if (chessboard[i][j - temp_i].color == 'b') break;
								chessboard[i][j - temp_i].state = selected;
								if (chessboard[i][j - temp_i].color == 'w') break;
							}
						}

					}
					else if (chessboard[i][j].type == 'n' && memory.last_piece.type == 'n') // movement of the black knight
					{
						if (i - 2 >= 0 && j - 1 >= 0)
						{
							chessboard[i - 2][j - 1].state = (chessboard[i - 2][j - 1].color == 'b') ? not_selected : selected;
						}
						if (i - 2 >= 0 && j + 1 < 8)
						{
							chessboard[i - 2][j + 1].state = (chessboard[i - 2][j + 1].color == 'b') ? not_selected : selected;
						}
						if (i + 2 < 8 && j - 1 >= 0)
						{
							chessboard[i + 2][j - 1].state = (chessboard[i + 2][j - 1].color == 'b') ? not_selected : selected;
						}
						if (i + 2 < 8 && j + 1 < 8)
						{
							chessboard[i + 2][j + 1].state = (chessboard[i + 2][j + 1].color == 'b') ? not_selected : selected;
						}
						if (i - 1 >= 0 && j - 2 >= 0)
						{
							chessboard[i - 1][j - 2].state = (chessboard[i - 1][j - 2].color == 'b') ? not_selected : selected;
						}
						if (i - 1 >= 0 && j + 2 < 8)
						{
							chessboard[i - 1][j + 2].state = (chessboard[i - 1][j + 2].color == 'b') ? not_selected : selected;
						}
						if (i + 1 < 8 && j - 2 >= 0)
						{
							chessboard[i + 1][j - 2].state = (chessboard[i + 1][j - 2].color == 'b') ? not_selected : selected;
						}
						if (i + 1 < 8 && j + 2 < 8)
						{
							chessboard[i + 1][j + 2].state = (chessboard[i + 1][j + 2].color == 'b') ? not_selected : selected;
						}

					}
			}


				//White pieces

				else if (chessboard[i][j].color == 'w'  && turn == 'w')//memory last piece used to deactivate selected squares from other pieces
				{
					if (chessboard[i][j].type == 'p' && memory.last_piece.type == 'p' && i-1>=0) //movement of the white pawn
					{
						chessboard[i - 1][j].state = (chessboard[i - 1][j].color == 'w' || chessboard[i - 1][j].color == 'b') ? not_selected : selected;
						if (chessboard[i - 2][j].color == ' ' && i - 2 >= 0 && chessboard[i][j].has_moved == false)
						{
							chessboard[i - 2][j].state = selected;
						}
						if (chessboard[i - 1][j - 1].color == 'b' && j-1>=0)
						{
							chessboard[i - 1][j - 1].state = selected;
						}
						if (chessboard[i - 1][j + 1].color == 'b' && j + 1 < 8)
						{
							chessboard[i - 1][j + 1].state = selected;
						}
						
					}
					else if (chessboard[i][j].type == 'b' && memory.last_piece.type == 'b') //moves of the white bishop
					{
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j + temp_i < 8)
							{
								if (chessboard[i + temp_i][j + temp_i].color == 'w') break;
								chessboard[i + temp_i][j + temp_i].state = selected;
								if (chessboard[i + temp_i][j + temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j - temp_i >= 0)
							{
								if (chessboard[i + temp_i][j - temp_i].color == 'w') break;
								chessboard[i + temp_i][j - temp_i].state = selected;
								if (chessboard[i + temp_i][j - temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j + temp_i < 8)
							{
								if (chessboard[i - temp_i][j + temp_i].color == 'w') break;
								chessboard[i - temp_i][j + temp_i].state = selected;
								if(chessboard[i - temp_i][j + temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j - temp_i].color == 'w') break;
								chessboard[i - temp_i][j - temp_i].state = selected;
								if (chessboard[i - temp_i][j - temp_i].color == 'b') break;

							}
						}
						
					}
					else if (chessboard[i][j].type == 'r' && memory.last_piece.type == 'r') //movement of the white rook
					{
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8)
							{
								if (chessboard[i + temp_i][j].color == 'w') break;
								chessboard[i + temp_i][j].state = selected;
								if (chessboard[i + temp_i][j].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j].color == 'w') break;
								chessboard[i - temp_i][j].state = selected;
								if (chessboard[i - temp_i][j].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j + temp_i < 8)
							{
								if (chessboard[i][j + temp_i].color == 'w') break;
								chessboard[i][j + temp_i].state = selected;
								if (chessboard[i][j + temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j - temp_i >= 0)
							{
								if (chessboard[i][j - temp_i].color == 'w') break;
								chessboard[i][j - temp_i].state = selected;
								if (chessboard[i][j - temp_i].color == 'b') break;
							}
						}
						
					}
					else if (chessboard[i][j].type == 'k' && memory.last_piece.type == 'k')//movement of the white king
					{
						if (i - 1 >= 0)
						{
							chessboard[i - 1][j].state = (chessboard[i - 1][j].color == 'w') ? not_selected : selected;
							if (j - 1 >= 0)
							{
								chessboard[i - 1][j - 1].state = (chessboard[i - 1][j - 1].color == 'w') ? not_selected : selected;
							}
						}
						if (i + 1 < 8)
						{
							chessboard[i + 1][j].state = (chessboard[i + 1][j].color == 'w') ? not_selected : selected;
							if (j + 1 < 8)
							{
								chessboard[i + 1][j + 1].state = (chessboard[i + 1][j + 1].color == 'w') ? not_selected : selected;
							}
						}
						if (j - 1 >= 0)
						{
							chessboard[i][j - 1].state = (chessboard[i][j - 1].color == 'w') ? not_selected : selected;
							if (i + 1 < 8)
							{
								chessboard[i + 1][j - 1].state = (chessboard[i + 1][j - 1].color == 'w') ? not_selected : selected;
							}
						}
						if (j + 1 < 8)
						{
							chessboard[i][j + 1].state = (chessboard[i][j + 1].color == 'w') ? not_selected : selected;
							if (i - 1 >= 0)
							{
								chessboard[i - 1][j + 1].state = (chessboard[i - 1][j + 1].color == 'w') ? not_selected : selected;
							}
						}
						
					}
					else if (chessboard[i][j].type == 'q' && memory.last_piece.type == 'q') //movement of the white queen
					{
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j + temp_i < 8)
							{
								if (chessboard[i + temp_i][j + temp_i].color == 'w') break;
								chessboard[i + temp_i][j + temp_i].state = selected;
								if (chessboard[i + temp_i][j + temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8 && j - temp_i >= 0)
							{
								if (chessboard[i + temp_i][j - temp_i].color == 'w') break;
								chessboard[i + temp_i][j - temp_i].state = selected;
								if (chessboard[i + temp_i][j - temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j + temp_i < 8)
							{
								if (chessboard[i - temp_i][j + temp_i].color == 'w') break;
								chessboard[i - temp_i][j + temp_i].state = selected;
								if (chessboard[i - temp_i][j + temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0 && j - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j - temp_i].color == 'w') break;
								chessboard[i - temp_i][j - temp_i].state = selected;
								if (chessboard[i - temp_i][j - temp_i].color == 'b') break;
							}
						}
						
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i + temp_i < 8)
							{
								if (chessboard[i + temp_i][j].color == 'w') break;
								chessboard[i + temp_i][j].state = selected;
								if (chessboard[i + temp_i][j].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (i - temp_i >= 0)
							{
								if (chessboard[i - temp_i][j].color == 'w') break;
								chessboard[i - temp_i][j].state = selected;
								if (chessboard[i - temp_i][j].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j + temp_i < 8)
							{
								if (chessboard[i][j + temp_i].color == 'w') break;
								chessboard[i][j + temp_i].state = selected;
								if (chessboard[i][j + temp_i].color == 'b') break;
							}
						}
						for (int temp_i = 1; temp_i < 8; temp_i++)
						{
							if (j - temp_i >= 0)
							{
								if (chessboard[i][j - temp_i].color == 'w') break;
								chessboard[i][j - temp_i].state = selected;
								if (chessboard[i][j - temp_i].color == 'b') break;
							}
						}
						
					}
					else if (chessboard[i][j].type == 'n' && memory.last_piece.type == 'n') // movement of the white knight
					{
						if (i - 2 >= 0 && j - 1 >= 0)
						{
							chessboard[i - 2][j - 1].state = (chessboard[i - 2][j - 1].color == 'w') ? not_selected : selected;
						}
						if (i - 2 >= 0 && j + 1 < 8)
						{
							chessboard[i - 2][j + 1].state = (chessboard[i - 2][j + 1].color == 'w') ? not_selected : selected;
						}
						if (i + 2 < 8 && j - 1 >= 0)
						{
							chessboard[i + 2][j - 1].state = (chessboard[i + 2][j - 1].color == 'w') ? not_selected : selected;
						}
						if (i + 2 < 8 && j + 1 < 8)
						{
							chessboard[i + 2][j + 1].state = (chessboard[i + 2][j + 1].color == 'w') ? not_selected : selected;
						}
						if (i - 1 >= 0 && j - 2 >= 0)
						{
							chessboard[i - 1][j - 2].state = (chessboard[i - 1][j - 2].color == 'w') ? not_selected : selected;
						}
						if (i - 1 >= 0 && j + 2 < 8)
						{
							chessboard[i - 1][j + 2].state = (chessboard[i - 1][j + 2].color == 'w') ? not_selected : selected;
						}
						if (i + 1 < 8 && j - 2 >= 0)
						{
							chessboard[i + 1][j - 2].state = (chessboard[i + 1][j - 2].color == 'w') ? not_selected : selected;
						}
						if (i + 1 < 8 && j + 2 < 8)
						{
							chessboard[i + 1][j + 2].state = (chessboard[i + 1][j + 2].color == 'w') ? not_selected : selected;
						}

					}
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
