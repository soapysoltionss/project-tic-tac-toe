

//ai-algo.c & ai-algo-easy.c
extern char player;
extern char ai_player;
bool empty_spots(char board_spots[3][3]);
int check_win(char b[3][3]);
int minimax(char board_spots[3][3], int depth, bool isMaxTurn);
extern struct Move findNextBestMove(char board_spots[3][3]);

int ez_minimax(char board_spots[3][3], int depth, bool isMaxTurn);
extern struct Move findNextMove(char board_spots[3][3]);