#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Game {

	unsigned int sq00 : 2;
	unsigned int sq01 : 2;
	unsigned int sq02 : 2;
	unsigned int sq03 : 2;
	unsigned int sq10 : 2;
	unsigned int sq11 : 2;
	unsigned int sq12 : 2;
	unsigned int sq13 : 2;
	unsigned int sq20 : 2;
	unsigned int sq21 : 2;
	unsigned int sq22 : 2;
	unsigned int sq23 : 2;
	unsigned int sq30 : 2;
	unsigned int sq31 : 2;
	unsigned int sq32 : 2;
	unsigned int sq33 : 2;

	unsigned int blue_white : 4;
	unsigned int blue_blue : 3;
	unsigned int blue_red : 3;

	unsigned int red_white : 4;
	unsigned int red_blue : 3;
	unsigned int red_red : 3;

	char mover;

};

bool validMove(struct Game game1, struct Game game2, char *moved)
{
	short unsigned int board1[16] = 
			{
				game1.sq00, game1.sq01, game1.sq02, game1.sq03, 
				game1.sq10, game1.sq11, game1.sq12, game1.sq13,
				game1.sq20, game1.sq21, game1.sq22, game1.sq13,
				game1.sq30, game1.sq31, game1.sq32, game1.sq33
			};	
	short unsigned int board2[16] = 
			{
				game2.sq00, game2.sq01, game2.sq02, game2.sq03, 
				game2.sq10, game2.sq11, game2.sq12, game2.sq13,
				game2.sq20, game2.sq21, game2.sq22, game2.sq13,
				game2.sq30, game2.sq31, game2.sq32, game2.sq33
			};

	short unsigned int i;
	short unsigned int ct; /* how many changed entries */
	if (*moved == 'w')
	{
		for (i = 0; i < 16; i++)
		{
			if (board1[i] != board2[i])
			{
				ct++;
				if ((board1[i] > 0) || (board2[i] != 1))
				{
					return false;
				}
			}
		}
		if (ct != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (*moved == 'r')
	{
		for (i = 0; i < 16; i++)
		{
			if (board1[i] != board2[i])
			{
				ct++;
				if ((board1[i] != 1) || (board2[i] != 2))
				{
					return false;
				}
			}
		}
		if (ct != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (*moved == 'b')
	{
		for (i = 0; i < 16; i++)
		{
			if (board1[i] != board2[i])
			{
				ct++;
				if ((board1[i] != 1) || (board2[i] != 3))
				{
					return false;
				}
			}
		}
		if (ct != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool moveOrder(struct Game game1, struct Game game2, char *mover)
{
	/* moveOrder - returns true if game2 has correct number
	 * of pieces based on game1 and writes the mover to mover
	 *
	 * if game2 has wrong number, nothing written, returns false
	 *
	 */

	int blue_pieces_1;
	int red_pieces_1;
	int blue_pieces_2;
	int red_pieces_2;
	
	blue_pieces_1 = game1.blue_white + game1.blue_blue + game1.blue_red;
	blue_pieces_2 = game2.blue_white + game2.blue_blue + game2.blue_red;

	red_pieces_1 = game1.red_white + game1.red_blue + game1.red_red;
	red_pieces_2 = game2.red_white + game2.red_blue + game2.red_red;

	if (blue_pieces_1 == red_pieces_1)
	{
		/* Then it was red's turn to move */
		if (red_pieces_2 == red_pieces_1-1)
		{
			*mover = 'r';
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (blue_pieces_1 == red_pieces_1-1)
	{
		/* then it was blue's turn to move */
		if (blue_pieces_2 == blue_pieces_1-1)
		{
			*mover = 'b';
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool pieceCount(struct Game game1, struct Game game2, char *mover, char *moved)
{
	/* At this point we have checked to see that the bulk
	 * number of pieces checks out, now we must check 
	 * that they are consistent within categories. 
	 *
	 */

	if (*mover == 'r')
	{
		if (
			(game1.blue_white == game2.blue_white) &&
			(game1.blue_red == game2.blue_red) &&
			(game1.blue_blue == game2.blue_blue)
		)
		{
			if (
				(game1.red_white-1 == game2.red_white) &&
				(game1.red_blue == game2.red_blue) &&
				(game1.red_red == game2.red_red)
			)
			{
				*moved = 'w';
				return true;
			}
			else if (
				(game1.red_white == game2.red_white) &&
				(game1.red_blue-1 == game2.red_blue) &&
				(game1.red_red == game2.red_red)
			)
			{
				*moved = 'b';
				return true;
			}
			else if (
				(game1.red_white == game2.red_white) &&
				(game1.red_blue == game2.red_blue) &&
				(game1.red_red-1 == game2.red_red)
			)
			{
				*moved = 'r';
				return true;
			}
			else
			{
				/* this should never happen */
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (*mover == 'b')
	{
		if (
			(game1.red_white == game2.red_white) &&
			(game1.red_blue == game2.red_blue) &&
			(game1.red_red == game2.red_red)
		)
		{
			if (
				(game1.blue_white-1 == game2.blue_white) &&
				(game1.blue_blue == game2.blue_blue) &&
				(game1.blue_red == game2.blue_red)
			)
			{
				*moved = 'w';
				return true;
			}
			else if (
				(game1.blue_white == game2.blue_white) &&
				(game1.blue_blue-1 == game2.blue_blue) &&
				(game1.blue_red == game2.blue_red)
			)
			{
				*moved = 'b';
				return true;
			}
			else if (
				(game1.blue_white == game2.blue_white) &&
				(game1.blue_blue == game2.blue_blue) &&
				(game1.blue_red-1 == game2.blue_red)
			)
			{
				*moved = 'r';
				return true;
			}
			else
			{
				/* this should never happen */
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool nextMove(struct Game game1, struct Game game2)
{
	/* the following conditions must hold for game2
	 * to be a valid next move for game1:
	 * 	
	 * 	1. Correct move order
	 * 	2. Valid move piece
	 * 	3. Valid piece placement
	 *
	 * For (1) to be the case, exactly one player must
	 * have one less piece and the player with one less
	 * piece must be the right person. 
	 *
	 * For (2) to be true, the piece missing in 
	 * (1) must be one that the moving player still had
	 * in game1
	 *
	 * For (3) to be true, the piece must be placed in 
	 * a valid position (one that was open to placement in 
	 * game1)
	 */

	/* move order */
	char mover;
	if (moveOrder(game1,game2, &mover))
	{
		/* piece count */
		char moved;

		if (pieceCount(game1,game2, &mover, &moved))
		{
			/* valid move */
			return validMove(game1,game2,&moved);
		}
		return false;
	}
	return false;
}
struct Game newGame()
{
	struct Game *game = malloc(sizeof(struct Game));
	(*game).sq00 = 0;
	(*game).sq01 = 0;
	(*game).sq02 = 0;
	(*game).sq03 = 0;
	(*game).sq10 = 0;
	(*game).sq11 = 0;
	(*game).sq12 = 0;
	(*game).sq13 = 0;
	(*game).sq20 = 0;
	(*game).sq21 = 0;
	(*game).sq23 = 0;
	(*game).sq30 = 0;
	(*game).sq31 = 0;
	(*game).sq32 = 0;
	(*game).sq33 = 0;

	(*game).blue_white = 8;
	(*game).red_white = 8;
	(*game).blue_blue = 4;
	(*game).red_blue = 4;
	(*game).blue_red = 4;
	(*game).red_red = 4;

	(*game).mover = 'r';

	return *game;
}

short unsigned int _boardPiece(struct Game *game, int x, int y)
{
	/// return the value at x,y
	
	if (x == 0 && y == 0)
		return (*game).sq00;
	if (x == 0 && y == 1)
		return (*game).sq01;
	if (x == 0 && y == 2)
		return (*game).sq02;
	if (x == 0 && y == 3)
		return (*game).sq03;
	if (x == 1 && y == 0)
		return (*game).sq10;
	if (x == 1 && y == 1)
		return (*game).sq11;
	if (x == 1 && y == 2)
		return (*game).sq12;
	if (x == 1 && y == 3)
		return (*game).sq13;
	if (x == 2 && y == 0)
		return (*game).sq20;
	if (x == 2 && y == 1)
		return (*game).sq21;
	if (x == 2 && y == 2)
		return (*game).sq22;
	if (x == 2 && y == 3)
		return (*game).sq23;
	if (x == 3 && y == 0)
		return (*game).sq30;
	if (x == 3 && y == 1)
		return (*game).sq31;
	if (x == 3 && y == 2)
		return (*game).sq32;
	if (x == 3 && y == 3)
		return (*game).sq33;
}
void printBoard(struct Game game)
{


	int i,x,y;
	short unsigned int piece;

	for (i = 0; i < 16; i++)
	{
		y = i % 4;
		x = (i - y)/4;

		piece = _boardPiece(&game,x,y);
		
		if (i % 4 == 0)
		{
			printf("\n");
		}
		if (piece == 0)
		{
			printf("0");
		}
		else if (piece == 1)
		{
			printf("w");
		}
		else if (piece == 2)
		{
			printf("r");
		}
		else if (piece == 3)
		{
			printf("b");
		}
		else
		{
			fprintf(stderr,"Error, invalid board entry! %d\n", piece);
			exit(-1);
		}
	}
	printf("\n");
}
void _valueUpdate(struct Game *game, int x, int y, int val)
{
	/// This is necessary because we can't pass a pointer to bitfields


	if (x == 0 && y == 0)
		(*game).sq00 = val;
	if (x == 0 && y == 1)
		(*game).sq01 = val;
	if (x == 0 && y == 2)
		(*game).sq02 = val;
	if (x == 0 && y == 3)
		(*game).sq03 = val;
	if (x == 1 && y == 0)
		(*game).sq10 = val;
	if (x == 1 && y == 1)
		(*game).sq11 = val;
	if (x == 1 && y == 2)
		(*game).sq12 = val;
	if (x == 1 && y == 3)
		(*game).sq13 = val;
	if (x == 2 && y == 0)
		(*game).sq20 = val;
	if (x == 2 && y == 1)
		(*game).sq21 = val;
	if (x == 2 && y == 2)
		(*game).sq22 = val;
	if (x == 2 && y == 3)
		(*game).sq23 = val;
	if (x == 3 && y == 0)
		(*game).sq30 = val;
	if (x == 3 && y == 1)
		(*game).sq31 = val;
	if (x == 3 && y == 2)
		(*game).sq32 = val;
	if (x == 3 && y == 3)
		(*game).sq33 = val;
}
void _setVal(struct Game *game,int x, int y,char piece)
{
	if (x < 0 || x > 3 || y < 0 || y > 3)
	{
		fprintf(stderr,"Off board error: %i,%i\n",x,y);
		exit(-1);
	}
	if (piece == 'w' && _boardPiece(game,x,y) == 0)
	{
		_valueUpdate(game,x,y,1);		
	}
	else if (piece == 'r' && _boardPiece(game,x,y) == 1)
	{
		_valueUpdate(game,x,y,2);
	}
	else if (piece == 'b' && _boardPiece(game,x,y) == 1)
	{
		_valueUpdate(game,x,y,3);
	}
	else
	{
		fprintf(stderr,"Cannot place piece %c on square of value %i",piece,_boardPiece(game,x,y));
		exit(-1);
	}
}

void move(struct Game *game, int x, int y, char piece)
{
	if ((*game).mover == 'r')
	{
		if (piece == 'r' && (*game).red_red > 0)
		{
			_setVal(game,x,y,piece);
			(*game).red_red--;
		}
		else if (piece == 'b' && (*game).red_blue > 0)
		{
			_setVal(game,x,y,piece);
			(*game).red_blue--;
		}
		else if (piece == 'w' && (*game).red_white > 0)
		{
			_setVal(game,x,y,piece);
			(*game).red_white--;
		}
		else
		{
			fprintf(stderr,"Invalid piece type: %c, r has r: %i b: %i w: %i", piece, (*game).red_red, (*game).red_blue, (*game).red_white);
			exit(-1);
		}
	}
	else if ((*game).mover == 'b')
	{
		if (piece == 'r' && (*game).blue_red > 0)
		{
			_setVal(game,x,y,piece);
			(*game).blue_red--;
		}
		else if (piece == 'b' && (*game).blue_blue > 0)
		{
			_setVal(game,x,y,piece);
			(*game).blue_blue--;
		}
		else if (piece == 'w' && (*game).blue_white > 0)
		{
			_setVal(game,x,y,piece);
			(*game).blue_white--;
		}
		else
		{
			fprintf(stderr,"Invalid piece type: %c, b has r: %i b: %i w: %i", piece, (*game).blue_red, (*game).blue_blue, (*game).blue_white);
			exit(-1);
		}
	}
	if ((*game).mover == 'r')
		(*game).mover = 'b';
	else
		((*game).mover = 'r');
}

void copyGame(struct Game *old_game,struct Game *new_game)
{
	(*new_game).sq00 = (*old_game).sq00;
	(*new_game).sq01 = (*old_game).sq01;
	(*new_game).sq02 = (*old_game).sq02;
	(*new_game).sq03 = (*old_game).sq03;
	(*new_game).sq10 = (*old_game).sq10;
	(*new_game).sq11 = (*old_game).sq11;
	(*new_game).sq12 = (*old_game).sq12;
	(*new_game).sq13 = (*old_game).sq13;
	(*new_game).sq20 = (*old_game).sq20;
	(*new_game).sq21 = (*old_game).sq21;
	(*new_game).sq22 = (*old_game).sq22;
	(*new_game).sq23 = (*old_game).sq23;
	(*new_game).sq30 = (*old_game).sq30;
	(*new_game).sq31 = (*old_game).sq31;
	(*new_game).sq32 = (*old_game).sq32;
	(*new_game).sq33 = (*old_game).sq33;

	(*new_game).red_white = (*old_game).red_white;
	(*new_game).red_red = (*old_game).red_red;
	(*new_game).red_blue = (*old_game).red_blue;
	
	(*new_game).blue_white = (*old_game).blue_white;
	(*new_game).blue_red = (*old_game).blue_red;
	(*new_game).blue_blue = (*old_game).blue_blue;

	(*new_game).mover = (*old_game).mover;
}

void movableSpaces(int *blank_board, int *white_board, struct Game game)
{
	// write the number of blank and white spaces in board to int ptrs
	int i,x,y;
	short unsigned int piece;

	for (i =  0; i < 16; i++)
	{
		y = i % 4;
		x = (i - y)/4;

		piece = _boardPiece(&game,x,y);

		if (piece == 0)
		{
			(*blank_board)++;
		}
		else if (piece ==  1)
		{
			(*white_board)++;
		}
	}
}
int nnGame(struct Game game)
{
	// return the number of possible next game states

	int white_moves,red_moves,blue_moves;
	int white_board = 0,blank_board = 0;
	int i;

	movableSpaces(&blank_board,&white_board,game);
	if (game.mover == 'r')
	{
		if ((game.red_white > 0) && (blank_board > 0))
			white_moves = blank_board;
		else
			white_moves = 0;
	       	
		if ((game.red_red > 0) && (white_board > 0))
			red_moves = white_board;
		else
			red_moves = 0;	
		if ((game.red_blue > 0) && (white_board > 0))
			blue_moves = white_board;
		else
			blue_moves = 0;

	}
	else if (game.mover == 'b')
	{
		if ((game.blue_white > 0) && (blank_board > 0))
			white_moves = blank_board;
		else
			white_moves = 0;
	       	
		if ((game.blue_red > 0) && (white_board > 0))
			red_moves = white_board;
		else
			red_moves = 0;	
		if ((game.blue_blue > 0) && (white_board > 0))
			blue_moves = white_board;
		else
			blue_moves = 0;
	}
	else
	{
		fprintf(stderr,"Invalid mover char: %c", game.mover);
		exit(-1);
	}
	return white_moves+blue_moves+red_moves;
}
void writeGame(struct Game *gptr)
{
	/// write a new game to a pointer

	(*gptr).sq00 = 0;
	(*gptr).sq01 = 0;
	(*gptr).sq02 = 0;
	(*gptr).sq03 = 0;
	(*gptr).sq10 = 0;
	(*gptr).sq11 = 0;
	(*gptr).sq12 = 0;
	(*gptr).sq13 = 0;
	(*gptr).sq20 = 0;
	(*gptr).sq21 = 0;
	(*gptr).sq23 = 0;
	(*gptr).sq30 = 0;
	(*gptr).sq31 = 0;
	(*gptr).sq32 = 0;
	(*gptr).sq33 = 0;

	(*gptr).blue_white = 8;
	(*gptr).red_white = 8;
	(*gptr).blue_blue = 4;
	(*gptr).red_blue = 4;
	(*gptr).blue_red = 4;
	(*gptr).red_red = 4;

	(*gptr).mover = 'r';
}
struct Game *nextGames(struct Game game)
{
	struct Game *next = (struct Game *)malloc(nnGame(game)*sizeof(struct Game));
	int i,x,y,piece,write_ind = 0;

	for (i = 0; i < 16; i++)
	{
		y = i % 4;
		x = (i - y)/4;
		piece = _boardPiece(&game,x,y);
		
		if (piece == 0)
		{
			if ((game.mover == 'r' && game.red_white > 0) || (game.mover == 'b' && game.blue_white > 0))
			{
				writeGame(next+(write_ind*sizeof(struct Game)));
				copyGame(&game,next+(write_ind*sizeof(struct Game)));
				move(next+(write_ind*sizeof(struct Game)),x,y,'w');
				write_ind++;
			}
		}
		else if (piece == 1)
		{
			if ((game.mover == 'r' && game.red_red >0) || (game.mover == 'b' && game.blue_red >0))
			{
				writeGame(next+(write_ind*sizeof(struct Game)));
				copyGame(&game,next+(write_ind*sizeof(struct Game)));
				move(next+(write_ind*sizeof(struct Game)),x,y,'r');
				write_ind++;
			}
			if ((game.mover == 'r' && game.red_blue >0) || (game.mover == 'b' && game.blue_blue >0))
			{
				writeGame(next+(write_ind*sizeof(struct Game)));
				copyGame(&game,next+(write_ind*sizeof(struct Game)));
				move(next+(write_ind*sizeof(struct Game)),x,y,'b');
				write_ind++;
			}
		}
	}
	
	return next;	
}

char isWin4(struct Game game)
{
	int row4[10][4] = {
		{0,4,8,12},
		{1,5,9,13},
		{2,6,10,14},
		{3,7,11,15},
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11},
		{12,13,14,15},
		{0,5,10,15},
		{12,9,6,3}
	};

	int line_index,i,x,y,j;
	int piece;
	int complete = false;

	for (line_index = 0; line_index < 10; line_index++)
	{
		i = row4[line_index][0];
		y = i % 4;
		x = (i-y)/4;	
		piece = _boardPiece(&game,x,y);

		for (j = 1; j < 4; j++)
		{
			if (piece == 0 || piece == 1)
				break;
		
			i = row4[line_index][j];
			y = i % 4;
			x = (i-y)/4;	
			
			if (_boardPiece(&game,x,y) != piece)
				break;
			if (j == 3)
			       complete	= true;
		}
		if (complete)
		{
			if (piece == 2)
				return 'r';
			else if (piece == 3)
				return 'b';
			else
				fprintf(stderr,"Invalid win condition! piece = %i",piece);
		}

	}
	return 'f';	
}
char isWin3(struct Game game)
{
	int row3[24][3] = {
		{0,4,8},
		{4,8,12},
		{1,5,9},
		{5,9,13},
		{2,6,10},
		{6,10,11},
		{3,7,11},
		{7,11,15},
		{0,1,2},
		{1,2,3},
		{4,5,6},
		{5,6,7},
		{8,9,10},
		{9,10,11},
		{12,13,14},
		{13,14,15},
		{4,9,14},
		{0,5,10},
		{5,10,15},
		{1,6,11},
		{8,5,2},
		{12,9,6},
		{9,6,3},
		{13,10,7}
	};

	int line_index,red_count=0,blue_count=0;
	int piece,i,j,x,y;
	int complete = false;

	for (line_index = 0; line_index < 24; line_index++)
	{
		complete = false;
		i = row3[line_index][0];	
		y = i % 4;
		x = (i-y)/4;

		piece = _boardPiece(&game,x,y);

		for (j = 1; j < 3; j++)
		{
			if (piece == 0 || piece == 1)
			      break;
			i = row3[line_index][j];
			y = i % 4;
			x = (i-y)/4;

			if (_boardPiece(&game,x,y) != piece)
				break;
			if (j == 2)
				complete = true;
		}

		if (complete && piece == 2)
			red_count++;
		if (complete && piece == 3)
			blue_count++;
		if (complete && !(piece == 2 || piece == 3))
			fprintf(stderr,"Invalid piece, but complete is true! %i\n",piece);
	}

	if (blue_count > red_count && blue_count > 2)
	       return 'b';
	if (red_count > blue_count && red_count > 2)
		return 'r';
	return 'f';	
}
int isWin(struct Game game)
{
	char win4 = isWin4(game);
	if (win4 == 'r' || win4 == 'b')
	{
		return true;
	}
	else
	{
		char win3 = isWin3(game);
		if (win3 == 'r' || win3 == 'b')
			return true;
	}
	return false;
}

int main()
{

	int i;
	struct Game game = newGame();
	
	printf("Starting game: %i\n",isWin(game));
	move(&game,0,0,'w');
	move(&game,0,1,'w');	
	move(&game,0,2,'w');	
	move(&game,0,3,'w');

	printf("White columns: %i\n",isWin(game));
	
	move(&game,0,0,'r');
	move(&game,0,1,'r');
	move(&game,0,2,'r');
	
	printf("3: %i\n", isWin(game));

	move(&game,0,3,'r');
	printf("4: %i\n", isWin(game));

	game = newGame();

	printf("Starting game: %i\n",isWin(game));

	move(&game,0,0,'w');
	move(&game,0,1,'w');	
	move(&game,0,2,'w');	
	move(&game,0,3,'w');
	move(&game,1,0,'w');
	move(&game,1,1,'w');	
	move(&game,1,2,'w');	
	move(&game,1,3,'w');
	move(&game,2,0,'w');
	move(&game,2,1,'w');	
	move(&game,2,2,'w');	
	move(&game,2,3,'w');
	move(&game,3,1,'w');	
	move(&game,3,2,'w');	
	move(&game,3,3,'w');
	move(&game,3,0,'w');	
	printf("isWin: %i\n",isWin(game));
	
	move(&game,2,0,'r');
	printBoard(game);
	move(&game,2,1,'r');
	printBoard(game);
	move(&game,2,2,'r');
	printBoard(game);
	move(&game,2,3,'b');
	printBoard(game);
	move(&game,3,0,'b');
	printBoard(game);
	move(&game,3,1,'r');	
	printBoard(game);
	move(&game,3,2,'r');	
	printBoard(game);
	move(&game,3,3,'r');
	printBoard(game);
	move(&game,0,0,'r');
	printBoard(game);
	move(&game,0,1,'r');
	printBoard(game);
	move(&game,0,2,'r');
	printBoard(game);
	move(&game,0,3,'r');
	printBoard(game);
		
	printf("isWin: %i\n",isWin(game));
}
