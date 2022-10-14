#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main();
int randomise_turns();
int board(); //create the board
int win(); //check for rows, columns or diagonals for win
bool empty_spots();
int maxVal(); // create the maximiser function
int minVal(); // create the minimiser function
int minimax(); // create the minimax function
int move(); // create the move function

// assumptions:
// 1) randomise players. Cannot be player or ai start first everytime
// 2) Do not allow the ai to pick the spot that is not empty

char player='x', ai='o', empty=' '; 
int row, col, depth, rand(void);
bool maxTurn;

char board_spots[3][3] = {
                         { 'o' , ' ' , 'x' }, 
                         { 'x' , ' ' , 'o' }, 
                         { 'o' , 'o' , 'x' }
                        };

int main() {
    randomise_turns();
    board();
    win(board_spots[row][col]);
}

// this function is to randmise between player or ai
int randomise_turns() {
    // randomise between 1 to 6
    // even number is player
    // odd number is ai
    srand(time(NULL));
    int rng = rand();

    if (rng%2 == 0) {
        printf("Player 1 Starts first!");
    } else {
        printf("AI will start first!");
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
        minimax(); 
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
int minimax() {
    // testing if i can call this function if there are empty spaces to start the minimax algo
    printf("in minimax function now");

    // call the max function
    maxVal();

    // call the min function
    minVal();
}

// max() is the maximiser function
int maxVal() {
    // create a variable called best for comparing the moves
    int best = -100;
    // for every row
    for (row = 0; row < 3; row++) {
        // for every col
        for (col = 0; col < 3; col++) {
            // check if theres an empty spot
            if (board_spots[row][col] == ' ') {
                // if its empty, make the move
                board_spots[row][col] = player;

                // if its the max value, choose it

            }
        }
    }
}

// // min() is the minimiser function
int minVal() {
    // create a variable called best for comparing the moves
    int best = 100;
    // for every row
    for (row = 0; row < 3; row++) {
        // for every col
        for (col = 0; col < 3; col++) {
            // check if theres an empty spot
            if (board_spots[row][col] == ' ') {
                // if its empty, make the move
                board_spots[row][col] == ai;

                // if its the best move, choose the max value

            }
        }
    }
}

// set the move into the board
int move() {
    // move is the best move, move to board_spots[row][col]
    // change the value of that spot from " " to "o" because its an AI
    // print the row and col of that spot in the board
}