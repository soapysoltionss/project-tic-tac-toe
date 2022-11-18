// C++ program to find the next optimal move for
// a player
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

struct Move
{
	int row, col;
};

char player = 'X', opponent = 'O';

// this function is to randmise between player or ai
int randomise_turns() {
    // generate a random number each time this function runs
    // create an int called rng (random number generator) 

    //generate number between diff seed where they will use the clock time as the seed
    srand(time(NULL));
    int rng = rand();

    // if the result of rng % is 0, means it is an even number, assign even number to player's turn
    // odd number is ai
    if (rng%2 == 0) {
        printf("Player 1 Starts first! \n\n");
    } else {
        // else, if the result of rng % is not 0, means it is an odd number, assign even number to AI's turn
        printf("AI will start first! \n\n");
    }
}

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]==' ')
				return true;
	return false;
}

// This is the evaluation function as discussed
// in the previous article ( http://goo.gl/sJgv68 )
int evaluate(char b[3][3])
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
		if (b[row][0]==b[row][1] &&
			b[row][1]==b[row][2])
		{
			if (b[row][0]==player)
				return +10;
			else if (b[row][0]==opponent)
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		if (b[0][col]==b[1][col] &&
			b[1][col]==b[2][col])
		{
			if (b[0][col]==player)
				return +10;

			else if (b[0][col]==opponent)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
		if (b[0][0]==player)
			return +10;
		else if (b[0][0]==opponent)
			return -10;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
		if (b[0][2]==player)
			return +10;
		else if (b[0][2]==opponent)
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
	int score = evaluate(board);

	// If Maximizer has won the game return his/her
	// evaluated score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie
	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]==' ')
				{
					// Make the move
					board[i][j] = player;

					// Call minimax recursively and choose
					// the maximum value
					best = max( best,
						minimax(board, depth+1, !isMax) );

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]==' ')
				{
					// Make the move
					board[i][j] = opponent;

					// Call minimax recursively and choose
					// the minimum value
					best = min(best,
						minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the player
struct Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	struct Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			// Check if cell is empty
			if (board[i][j]==' ')
			{
				// Make the move
				board[i][j] = player;

				// compute evaluation function for this
				// move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = ' ';

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	printf("The value of the best Move is : %d\n\n",
			bestVal);

	return bestMove;
}

// Driver code
int main()
{
	char board[3][3] =
	{
		{ 'X', ' ', ' ' },
		{ ' ', ' ', ' ' },
		{ 'O', ' ', 'O' }
	};

	struct Move bestMove = findBestMove(board);

	printf("The Optimal Move is :\n");
	printf("ROW: %d COL: %d\n\n", bestMove.row, bestMove.col );
	return 0;
}
