//Tic-tac-toe playing AI. Exhaustive tree-search. WTFPL
//Matthew Steel 2009, www.www.repsilat.com

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void draw(int b[9]) {
    printf(" %c | %c | %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
}

int win(const int board_spots[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board_spots[wins[i][0]] != 0 
        && board_spots[wins[i][0]] == board_spots[wins[i][1]] 
        && board_spots[wins[i][0]] == board_spots[wins[i][2]])
        return board_spots[wins[i][2]];
    }
    return 0;
}

int minimax(int board_spots[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board_spots);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    //For all moves,
    for(i = 0; i < 9; ++i) {
        // if spot is empty
        if(board_spots[i] == 0) {
            //Place the letter x into that spot
            board_spots[i] = player;
            int bestScore = -minimax(board_spots, player*-1);
            //Pick the one that's worst for the opponent
            if(bestScore > score) {
                score = bestScore;
                move = i;
            }
            //Change the spot to empty after checking value
            board_spots[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board_spots[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board_spots[i] == 0) {
            board_spots[i] = 1;
            int bestScore = -minimax(board_spots, -1);
            board_spots[i] = 0;
            if(bestScore > score) {
                score = bestScore;
                move = i;
            }
        }
    }
    //returns score for that spot
    board_spots[move] = 1;
}

void playerMove(int board_spots[9]) {
    int move = 0;
    do {
        start:
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        if(board_spots[move] != 0) {
        printf("Its Already Occupied !");
        goto start;
    }
    printf("\n");
    } while (move >= 9 || move < 0 && board_spots[move] == 0);
    board_spots[move] = -1;
}

int main() {
    int board_spots[9] = {0,0,0,0,0,0,0,0,0};
    //computer squares are 1, player squares are -1.
    printf("Computer: O, You: X\nPlay (1)st or (2)nd? ");
    int player=0;
    scanf("%d",&player);
    printf("\n");
    unsigned turn;
    for(turn = 0; turn < 9 && win(board_spots) == 0; ++turn) {
        if((turn+player) % 2 == 0)
            computerMove(board_spots);
        else {
            draw(board_spots);
            playerMove(board_spots);
        }
    }
    switch(win(board_spots)) {
        case 0:
            printf("This game is a draw\n");
            break;
        case 1:
            draw(board_spots);
            printf("You lose.\n");
            break;
        case -1:
            printf("You win. Inconceivable!\n");
            break;
    }
}