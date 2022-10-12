#include <stdio.h>
#include <stdbool.h>

int main();
int board();
int minimax();
int min();
int max();
int win();

char player='x', ai='o', empty=' '; 
int row, col;
char board_spots[3][3] = {
                         { 'o' , 'o' , 'x' }, 
                         { ' ' , 'o' , 'o' }, 
                         { ' ' , ' ' , 'o' }
                        };

int main() {
    board();
    win(board_spots[row][col]);
    minimax();
    min();
    max();
}

// this function is to read the board location for eg

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

            printf("row[%d], col[%d] = %d \n", row,col,board_spots[row][col]);
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
    if (board_spots[0][0] == board_spots[1][1] && board_spots[1][1] == board_spots[2][2]
    || board_spots[0][2] == board_spots[1][1] && board_spots[1][1] == board_spots[2][0]) {
            if (board_spots[0][0] == 'x' || board_spots[0][2] == 'x') {
                printf("Player1 wins with x on diagonal");
            }
            else if (board_spots[0][0] == 'o') {
                printf("AI wins with o on diagonal");
            } 
            else {
                return 0;
            }
    }
    // After checking for rows, columns and diagonal for wins, if there are no winner, then return 0 to continue the game
    return 0;
}

// max() is the maximiser function
int max() {

}

// min() is the minimiser function
int min() {

}

// minimax function to run the minimax algorithm
int minimax() {

}