// C program to find the next best move for AI
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

// Create a structure for move object 
// where the return value should give us row and col
struct Move
{
	int row, col;
};

// Create x for player and o for opponent
char player = 'X', opponent = 'O';

// This function is to check if there are empty spots in the board
bool empty_spots(char board[3][3])
{
	// for every row
	for (int i = 0; i<3; i++)
		// for every column
		for (int j = 0; j<3; j++)
			// if there are empty spots
			if (board[i][j]==' ')
				// return true
				return true;
	// else return false
	return false;
}

// This is the check for win function
int check_win(char b[3][3])
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
		// if there is a row that column 0 == 1 and 1 == 2
		if (b[row][0]==b[row][1] &&
			b[row][1]==b[row][2])
		{	
			// if row 0 symbol represents player which is X
			if (b[row][0]==player)
				// return +10 for player
				return +10;
			// else if row 0 symbol represents opponent which is )
			else if (b[row][0]==opponent)
				// return -10 for player
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		// if there is a row that column 0 == 1 and 1 == 2
		if (b[0][col]==b[1][col] &&
			b[1][col]==b[2][col])
		{
			// if row 0 symbol represents player which is X
			if (b[0][col]==player)
				// return +10 for player
				return +10;
			// else if row 0 symbol represents opponent which is O
			else if (b[0][col]==opponent)
				// return -10 for player
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	// if row 0 col 0 is == row 1 col 1 && 
	// row 1 col 1 is == row 2 col 2
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
		// if row 0 col 0 symbol represents player which is X		
		if (b[0][0]==player)
			// return +10 for player
			return +10;
		// else if row 0 col 0 symbol represents opponent which is O
		else if (b[0][0]==opponent)
			// return -10 for player
			return -10;
	}

	// Checking for Diagonals for X or O victory.
	// if row 0 col 2 is == row 1 col 1 && 
	// row 1 col 1 is == row 2 col 0
	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
		// if row 0 col 2 symbol represents player which is X		
		if (b[0][2]==player)
			// return -10 for player
			return +10;
		// else if row 0 col 2 symbol represents opponent which is O
		else if (b[0][2]==opponent)
			// return -10 for player
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
	// create an int variable called score
	// give the score if there is a win
	int score = check_win(board);

	// If Maximizer has won the game return his/her score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie
	if (empty_spots(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Check for every row
		for (int i = 0; i<3; i++)
		{
			// check for every col
			for (int j = 0; j<3; j++)
			{
				// Check if spot is empty
				if (board[i][j]==' ')
				{
					// Put X into the spot
					board[i][j] = player;

					// Call minimax recursively and choose the highest value
					best = max(best, minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
		// return the best value for maximiser turn
		// where 10 is the score for the best spot for maximiser
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// For every row
		for (int i = 0; i<3; i++)
		{
			// for every col
			for (int j = 0; j<3; j++)
			{
				// Check if spot is empty
				if (board[i][j]==' ')
				{
					// Put O into the spot
					board[i][j] = opponent;

					// Call minimax recursively and choose the lowest value
					best = min(best, minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
		// return the best value for minimiser turn
		// where 10 is the score for the best spot for minimiser
		return best;
	}
}

// This will return the best possible move for the player who is X
// create a struct object called find best move so that it will return row and col
struct Move findBestMove(char board[3][3])
{
	// Create a value for best val of -1000
	int bestVal = -1000;
	// Create a structure Move called best move
	struct Move bestMove;
	// let the row be -1
	bestMove.row = -1;
	// let the col be -1
	bestMove.col = -1;

	// For every row
	for (int i = 0; i<3; i++)
	{
		// for every col
		for (int j = 0; j<3; j++)
		{
			// Check if spot is empty
			if (board[i][j]==' ')
			{
				// Make the move for player which is X 
				board[i][j] = player;

				// call the minimax function for next move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = ' ';

				// If the value of the current move is
				// higher than the best value, then update
				// best move value

				// if moveVal is higher than BestVal
				if (moveVal > bestVal)
				{
					// set the bestMove.row 
					// to the current move Val row which is i
					bestMove.row = i;
					// set the Best.col 
					// to the current move Val col which is j
					bestMove.col = j;
					// let the new value of best val 
					// to be the current move val
					bestVal = moveVal;
				}
			}
		}
	}
	// print the value of the best move after computing minimax function
	printf("The value of the best Move is : %d\n\n", bestVal);
	// return the new best move
	return bestMove;
}

// Main function
int main()
{
	// create a board of 2d array of 3x3
	char board[3][3] =
	{
		// use static board to check the minimax function 
		{ 'X', 'X', 'O' },
		{ 'X', 'O', 'O' },
		{ ' ', ' ', ' ' }
	};

	// The structure bestMove 
	// should get the bestMove of the new spot 
	struct Move bestMove = findBestMove(board);

	// Print the best move is
	printf("The Best Move is :\n");
	// printt the row and col of the new best move
	printf("ROW: %d COL: %d\n\n", bestMove.row, bestMove.col );
	return 0;
}
