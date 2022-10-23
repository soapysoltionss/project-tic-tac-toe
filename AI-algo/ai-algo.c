#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// assumptions:
// 1) randomise players. Cannot be player or ai start first everytime
// 2) Do not allow the ai to pick the spot that is not empty

char player='x', ai='o', empty=' '; 
int row, col, depth, rand(void);
bool maxTurn; // true if it is the maximiser turn and false of its the minimiser turn

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

char board_spots[3][3] = {
                         { ' ' , ' ' , 'x' }, 
                         { 'x' , ' ' , 'o' }, 
                         { 'o' , 'o' , 'x' }
                        };

int main();
int randomise_turns();
int board(); //create the board
int win(); //check for rows, columns or diagonals for win
bool empty_spots();
int minimax(char board_spots[row][col], int depth, bool maxTurn); // create the minimax function
int move(); // create the move function

int main() {
    randomise_turns();
    board();
    win(board_spots[row][col]);
}

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


// this function is to read the board location

int board() {
    // declare row and col as 0 because array starts from 0
    // declare array and the size and put the number in the array
    //loop for row
    for (row = 0; row < 3; ++row) {
        //loop for col
        for (col = 0; col < 3; ++col) {
            //for each row, col print the number in the box for eg

            //         Col0    Col1    Col2
            // Row0   0 , 0 | 0 , 1  | 0 , 2
            //        _Box0_|__Box1__|_Box2_              
            // Row1   1 , 0 | 1 , 1  | 1 , 2
            //        _Box3_|__Box4__|_Box5_
            // Row2   2 , 0 | 2 , 1  | 2 , 2
            //         Box6 |  Box7  | Box8

            printf("row[%d], col[%d] = %d \n", row, col, board_spots[row][col]);
        }
    }
    printf("\n");
    return 0;
}

// function to check if there is a winner
int win() {
    // check for row wins
    // for loop for every row
    // check if column 0, 1, 2 are the same
    // if they are they same, then check char,
    // check if player or AI won
    // esle if column are not the same, return 0
    for (row = 0; row < 3; ++row) {
        if (board_spots[row][0] == board_spots[row][1] 
        && board_spots[row][1] == board_spots[row][2]) {
            if (board_spots[row][0] == 'x') {
                printf("Player1 wins with x on row");
            }
            else if (board_spots[row][0] == 'o') {
                printf("AI wins with o on row");
            } 
            else {
                return 0;
            }
        }
    }

    // check for column wins
    // for loop for every column
    // check if row 0, 1, 2 are the same
    // if they are they same, then check char,
    // check if player or AI won
    // esle if row are not the same, return 0
    for (col = 0; col < 3; ++col) {
        if (board_spots[0][col] == board_spots[1][col] 
        && board_spots[1][col] == board_spots[2][col]) {
            if (board_spots[0][col] == 'x') {
                printf("Player1 wins with x on column");
            }
            else if (board_spots[0][col] == 'o') {
                printf("AI wins with o on column");
            } 
            else {
                return 0;
            }
        }
    }

    // check for diagonal wins
    // check if box 0, 4, 8 OR box 3, 4, 6 are the same
    // box 0 = [0][0], box 4 = [1][1] , box 8 = [2][2], box 3 = [1][0], box 4 = [1][1], box 6 = [2][0]

    // check for diagonal win in "\" slope
    if (board_spots[0][0] == board_spots[1][1] && board_spots[1][1] == board_spots[2][2]) {
            if (board_spots[0][0] == 'x') {
                printf("Player1 wins with x on diagonal");
            }
            else if (board_spots[0][0] == 'o') {
                printf("AI wins with o on diagonal");
            } 
            else {
                return 0;
            }
    }
    // check for the diagonal win in "/" slope
        if (board_spots[0][2] == board_spots[1][1] && board_spots[1][1] == board_spots[2][0]) {
            if (board_spots[0][2] == 'x') {
                printf("Player1 wins with x on diagonal");
            }
            else if (board_spots[0][2] == 'o') {
                printf("AI wins with o on diagonal");
            } 
            else {
                return 0;
            }
    }

    // if empty_spots function returns true, 
    if (empty_spots() == true) {
        // run minimax algorithm
        minimax(board_spots, depth, maxTurn); // call the minimax function
    }
    // if empty_spots function returns false, then print this game is a tie because there are no winnners
    else {
        printf("This game is a Tie!");   
    }
}

bool empty_spots() {
    // After checking for rows, columns and diagonal for wins, 
    // if there are no winner, 
    // check if there are empty spots,

    // add a variable for empty spot and set to 0
    // once it hit 1 then return true

    int empty = 0;
    int not_empty = 0;

    for (row = 0; row < 3; ++row) {
        for (col = 0; col < 3; ++col) {
            if (board_spots[row][col] == ' ') {
            // if there are, then add 1 to empty
                empty += 1;
            }
            // else, add 1 to not empty 
            else { 
                not_empty += 0;
            } 
        }
    }

    if (empty >= 1) {
    // if there are, then return true,
        return true;
    }
    // else, return false  
    else { 
        return false;
    } 
    
}

// minimax function to run the minimax algorithm
int minimax(char board_spots[row][col], int depth, bool maxTurn) {
    // if it is maximiser turn then run the code below
    if (maxTurn) {
    // create a variable called maxVal for comparing the values and taking the maximum value
    float maxVal = -INFINITY;
    // for every row
    for (row = 0; row < 3; row++) {
        // for every col
        for (col = 0; col < 3; col++) {
            // check if theres an empty spot
            if (board_spots[row][col] == ' ') {
                // if its empty, make the move
                board_spots[row][col] = 'x';

                // if its the max value, choose it
                // Call minimax recursively and choose
                // the maximum value
                maxVal = max(maxVal, minimax(board_spots, depth+1, !maxTurn));

                printf("max vale at line 223 = %d", maxVal);
                // change the spot back to ' '
                board_spots[row][col] = ' ';
            }
        }
    }
    return maxVal;
    } else {
    // else if it is !maximiser turn then run the code below
    // create a variable called minVal for comparing the values and taking the minimum value
    float minVal = INFINITY;
    // for every row
    for (row = 0; row < 3; row++) {
        // for every col
        for (col = 0; col < 3; col++) {
            // check if theres an empty spot
            if (board_spots[row][col] == ' ') {
                // if its empty, make the move
                board_spots[row][col] == 'o';

                // if its the best move, choose the max value
                // Call minimax recursively and choose
                // the maximum value
                minVal = min(minVal, minimax(board_spots, depth+1, !maxTurn));

                printf("min vale at line 223 = %d", minVal);
                
                // change the spot back to ' '
                board_spots[row][col] = ' ';
            }
        }
    }
    return minVal;
    }
}

// set the move into the board
int move(char board_spots[row][col]) {
    float oldBestMove = -INFINITY;
    int newBestMove = 0;
    int new_row = -1;
    int new_col = -1;

    // check for all empty spots, run the minimax function
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 2; col++) {
            if (board_spots[row][col] == ' ') {
                
                // change the value of that spot from " " to "o" because its an AI
                board_spots[row][col] == ai;

                // run the minimax function
                int bestMove = minimax(board_spots, 0 , false);

                board_spots[row][col] == ' ';

                // move is the best move, move to board_spots[row][col]
                if (bestMove > oldBestMove) {
                    new_row = row;
                    printf("The row of the best move is: %d", new_row);
                    new_col = col;
                    printf("The column of the best move is: %d", new_col);
                    newBestMove = bestMove;
                    printf("The value is %d", newBestMove);
                }
            }
        }
    }
}