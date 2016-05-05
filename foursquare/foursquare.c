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

	return *game;
}
short unsigned int *gameBoardToArray(struct Game game)
{
	short unsigned int *board = malloc(sizeof(short unsigned int)*16);
	*(board) = game.sq00;
	*(board+sizeof(short unsigned int)) = game.sq01;
	*(board+sizeof(short unsigned int)*2) = game.sq02;
	*(board+sizeof(short unsigned int)*3) = game.sq03;
	*(board+sizeof(short unsigned int)*4) = game.sq10;
	*(board+sizeof(short unsigned int)*5) = game.sq11;
	*(board+sizeof(short unsigned int)*6) = game.sq12;
	*(board+sizeof(short unsigned int)*7) = game.sq13;
	*(board+sizeof(short unsigned int)*8) = game.sq20;
	*(board+sizeof(short unsigned int)*9) = game.sq21;
	*(board+sizeof(short unsigned int)*10) = game.sq22;
	*(board+sizeof(short unsigned int)*11) = game.sq23;
	*(board+sizeof(short unsigned int)*12) = game.sq30;
	*(board+sizeof(short unsigned int)*13) = game.sq31;
	*(board+sizeof(short unsigned int)*14) = game.sq32;
	*(board+sizeof(short unsigned int)*15) = game.sq33;

	return board;
}

void printBoard(struct Game game)
{
	short unsigned int *board;
	board = gameBoardToArray(game);
	int i;
	for (i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
		{
			printf("\n");
		}
		if (*(board+i*2) == 0)
		{
			printf("0");
		}
		else if (*(board+i*2) == 1)
		{
			printf("w");
		}
		else if (*(board+i*2) == 2)
		{
			printf("r");
		}
		else if (*(board+i*2) == 3)
		{
			printf("b");
		}
		else
		{
			printf("Error, invalid board entry! %d", *(board+i));
		}
	}
	printf("\n");
}
void _setVal(unsigned int square,char piece)
{
	if (piece == 'w' && (square) == 0)
	{
		(square)= 1;
	}
	else if (piece == 'r' && (square) == 1)
	{
		(square)= 2;
	}
	else if (piece == 'b' && (square) == 1)
	{
		(square)= 3;
	}
	else
	{
		fprintf(stderr,"Cannot place piece %c on square of value %i",piece,(square));
		exit(-1);
	}
}

void _place(struct Game *game, int x, int y, char piece)
{

	switch(x) {
		case 0:
			switch(y) {
				case 0:
					_setVal((*game).sq00,piece);
				case 1:
					_setVal((*game).sq01,piece);
				case 2:
					_setVal((*game).sq02,piece);
				case 3:
					_setVal((*game).sq03,piece);
				default:
					fprintf(stderr,"Invalid indices x: %i, y: %i", x,y);
					exit(-1);
			}
		case 1:
			switch(y) {
				case 0:
					_setVal((*game).sq10,piece);
				case 1:
					_setVal((*game).sq11,piece);
				case 2:
					_setVal((*game).sq12,piece);
				case 3:
					_setVal((*game).sq13,piece);
				default:
					fprintf(stderr,"Invalid indices x: %i, y: %i", x,y);
					exit(-1);
			}
		case 2:
			switch(y) {
				case 0:
					_setVal((*game).sq20,piece);
				case 1:
					_setVal((*game).sq21,piece);
				case 2:
					_setVal((*game).sq22,piece);
				case 3:
					_setVal((*game).sq23,piece);
				default:
					fprintf(stderr,"Invalid indices x: %i, y: %i", x,y);
					exit(-1);
			}
		case 3:
			switch(y) {
				case 0:
					_setVal((*game).sq30,piece);
				case 1:
					_setVal((*game).sq31,piece);
				case 2:
					_setVal((*game).sq32,piece);
				case 3:
					_setVal((*game).sq33,piece);
				default:
					fprintf(stderr,"Invalid indices x: %i, y: %i", x,y);
					exit(-1);
			}
		default:
				fprintf(stderr,"Invalid indices x: %i, y: %i", x,y);
				exit(-1);
	}
}
void move(struct Game *game, int x, int y, char mover, char piece)
{
	if (mover == 'r')
	{
		if (piece == 'r' && (*game).red_red > 0)
		{
			_place(game,x,y,piece);
			(*game).red_red--;
		}
		else if (piece == 'b' && (*game).red_blue > 0)
		{
			_place(game,x,y,piece);
			(*game).red_blue--;
		}
		else if (piece == 'w' && (*game).red_white > 0)
		{
			_place(game,x,y,piece);
			(*game).red_white--;
		}
		else
		{
			fprintf(stderr,"Invalid piece type: %c, r has r: %i b: %i w: %i", piece, (*game).red_red, (*game).red_blue, (*game).red_white);
		}
	}
	else if (mover == 'b')
	{
		if (piece == 'r' && (*game).blue_red > 0)
		{
			_place(game,x,y,piece);
			(*game).blue_red--;
		}
		else if (piece == 'b' && (*game).blue_blue > 0)
		{
			_place(game,x,y,piece);
			(*game).blue_blue--;
		}
		else if (piece == 'w' && (*game).blue_white > 0)
		{
			_place(game,x,y,piece);
			(*game).blue_white--;
		}
		else
		{
			fprintf(stderr,"Invalid piece type: %c, b has r: %i b: %i w: %i", piece, (*game).blue_red, (*game).blue_blue, (*game).blue_white);
		}
	}
}
struct Game *nextGames(struct Game game, char *mover)
{
	// return a pointer to memory chunk containing 
	// the possible next game states of game
	
	int poss_gamestates = nnGame(game,mover);
	struct Game *gamechunk = malloc(poss_gamestates*sizeof(struct Game));

}
void movableSpaces(int *blank_board, int *white_board, short unsigned int *board)
{
	// write the number of blank and white spaces in board to int ptrs
	int i;
	for (i =  0; i < 16; i++)
	{
		if (*(board+i*2) == 0)
		{
			(*blank_board)++;
		}
		else if (*(board+i*2)==  1)
		{
			(*white_board)++;
		}
	}
}
int nnGame(struct Game game, char *mover)
{
	// return the number of possible next game states

	int white_moves,red_moves,blue_moves;
	int white_board = 0,blank_board = 0;
	short unsigned int *board =  gameBoardToArray(game);
	int i;

	movableSpaces(&blank_board,&white_board,board);
	if (*mover == 'r')
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
	else if (*mover == 'b')
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
		fprintf(stderr,"Invalid mover char: %c", *mover);
		exit(-1);
	}
	return white_moves+blue_moves+red_moves;
}

int main()
{
	struct Game game1 = newGame();
	struct Game game2 = newGame();
	printf("\ngame 1\n");	
	printBoard(game1);
	
	
	if (nextMove(game1,game2))
	{
		printf("\nyes");
	}
	else
	{
		printf("\nno");
	}

	_setVal(game2.sq00,'w');
	printBoard(game2);
	
	move(&game2, 0, 0, 'r','w');	
	printf("\ngame 2\n");
	printBoard(game2);
	
	if (nextMove(game1,game2))
	{
		printf("\nyes");
	}
	else
	{
		printf("\nno");
	}
	
	printf("\nSize of a game: %i\n",sizeof(struct Game));
	printf("\nSize of an int: %i\n",sizeof(double));
	
	char mover = 'r';

	printf("\nNumber of possible moves for game1: %i\n", nnGame(game1,&mover));
	mover = 'b';
	printf("\nNumber of possible moves for game2: %i\n", nnGame(game2,&mover));

	return 0;
}
