#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

static char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
static char tile[2] = " \0";
static int currentMode = 0; //0->2P mode, 1->AI mode...

/*
const char mode[4][25]={"2-Player Mode",
                        "1-Player Mode (AI)",
                        "1-Player Mode (ML-ez)",
                        "1-Player Mode (ML-hard)"};
*/
const char mode[4][25]={"2-Player Mode",
                        "AI-Bot Mode",
                        "Easy-Bot Mode",
                        "Hard-Bot Mode"};

const char PLAYER[2] = {'X','O'};
char playerName[2][15] = {"Player 1","Player 2"};
int turn = 0; //for turn counter (reset on board reset) + turn%2 = player

static int x_win, o_win, ai_win, easy_win, hard_win;


void printBoard();
void resetBoard();
int checkFreeSpaces();
bool win();
void updateBoard(int x, int y,GtkWidget *widget, gpointer button);

static void activate (GtkApplication *app, gpointer data);
static void print_home_button(GtkWidget *widget, gpointer data);
static void two_p_mode(GtkWidget *widget, gpointer data);
static void ai_mode(GtkWidget *widget, gpointer data);
static void ml_ez_mode(GtkWidget *widget, gpointer data);
static void ml_hard_mode(GtkWidget *widget, gpointer data);
static void button00(GtkWidget *widget, gpointer data);
static void button01(GtkWidget *widget, gpointer data);
static void button02(GtkWidget *widget, gpointer data);
static void button10(GtkWidget *widget, gpointer data);
static void button11(GtkWidget *widget, gpointer data);
static void button12(GtkWidget *widget, gpointer data);
static void button20(GtkWidget *widget, gpointer data);
static void button21(GtkWidget *widget, gpointer data);
static void button22(GtkWidget *widget, gpointer data);
static void print_credits(GtkWidget *widget, gpointer data);
static void disableTTT();
static void enableTTT();

static GtkWidget *b00,*b01,*b02,*b10,*b11,*b12,*b20,*b21,*b22;
static GtkWidget *two_p, *ai, *ml_easy, *ml_hard;
static GtkWidget *xScore,*oScore,*aiScore,*easyScore,*hardScore;

int main(int argc, char **argv){
    GtkApplication *app;
    int status;
    
    //app = gtk_application_new("org.gtk.example",G_APPLICATION_DEFAULT_FLAGS);
    app = gtk_application_new("TIC.TAC.TOE",G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status = g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    
    return status;
}


//TICTACTOE FUNCTIONS
void printBoard()
{
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}
void resetBoard(){
    for (int x=0;x<3;x++){
        for (int y=0;y<3;y++){
            board[x][y] = ' ';
        }
    }
    turn=0; //reset turn
    tile[0] = ' ';
    gtk_button_set_label ((gpointer)b00, tile);
    gtk_button_set_label ((gpointer)b01, tile);
    gtk_button_set_label ((gpointer)b02, tile);
    gtk_button_set_label ((gpointer)b10, tile);
    gtk_button_set_label ((gpointer)b11, tile);
    gtk_button_set_label ((gpointer)b12, tile);
    gtk_button_set_label ((gpointer)b20, tile);
    gtk_button_set_label ((gpointer)b21, tile);
    gtk_button_set_label ((gpointer)b22, tile);
    enableTTT();
}
int checkFreeSpaces(){
    int fs = 9;
    for (int x=0;x<3;x++){
        for (int y=0;y<3;y++){
            if (board[x][y] != ' '){
                fs--;
            }
        }
    }
    return fs;
}
bool win(){
    // check for row wins
    // for loop for every row
    // check if column 0, 1, 2 are the same
    // if they are they same, then check char,
    // check if player or AI won
    // esle if column are not the same, return 0
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] 
        && board[row][1] == board[row][2]) {
            if (board[row][0] == 'X') {
                printf("%c wins with x on row \n",PLAYER[(turn-1)%2]);
                return true;
            }
            else if (board[row][0] == 'O') {
                printf("%c wins with o on row \n",PLAYER[(turn-1)%2]);
                return true;
            } 
            else {
                return false;
            }
        }
    }

    // check for column wins
    // for loop for every column
    // check if row 0, 1, 2 are the same
    // if they are they same, then check char,
    // check if player or AI won
    // esle if row are not the same, return 0
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] 
        && board[1][col] == board[2][col]) {
            if (board[0][col] == 'X') {
                printf("%c wins with x on column \n",PLAYER[(turn-1)%2]);
                return true;
            }
            else if (board[0][col] == 'O') {
                printf("%c wins with o on column \n",PLAYER[(turn-1)%2]);
                return true;
            } 
            else {
                return false;
            }
        }
    }

    // check for diagonal wins
    // check if box 0, 4, 8 OR box 3, 4, 6 are the same
    // box 0 = [0][0], box 4 = [1][1] , box 8 = [2][2], box 3 = [1][0], box 4 = [1][1], box 6 = [2][0]
    // check for diagonal win in "\" slope
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == 'X') {
                printf("%c wins with x on diagonal \n",PLAYER[(turn-1)%2]);
                return true;
            }
            else if (board[0][0] == 'O') {
                printf("%c wins with o on diagonal \n",PLAYER[(turn-1)%2]);
                return true;
            } 
            else {
                return false;
            }
    }
    // check for the diagonal win in "/" slope
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == 'X') {
                printf("%c wins with x on diagonal \n",PLAYER[(turn-1)%2]);
                return true;
            }
            else if (board[0][2] == 'O') {
                printf("%c wins with o on diagonal \n",PLAYER[(turn-1)%2]);
                return true;
            } 
            else {
                return false;
            }
    }
    return false;
}


//GTK GUI FUNCTIONS
static void activate (GtkApplication *app, gpointer data){
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *menu, *quit, *credits, *resetButton, *txtButton;
    //GtkWidget *b00,*b01,*b02,*b10,*b11,*b12,*b20,*b21,*b22;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Tic-Tac-Toe");

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window),grid);


    txtButton = gtk_button_new_with_label("TIC-TAC-TOE");
    gtk_widget_set_sensitive(txtButton, FALSE);
    gtk_grid_attach(GTK_GRID(grid), txtButton, 0,0,14,1);
    txtButton = gtk_button_new_with_label("SETTING");
    //g_signal_connect(msgButton, "clicked", G_CALLBACK(print_home_button),NULL);
    gtk_grid_attach(GTK_GRID(grid), txtButton, 14,0,2,1);


    //https://stackoverflow.com/questions/16630528/trying-to-populate-a-gtkcombobox-with-model-in-c
    //https://github.com/steshaw/gtk-examples/blob/master/ch05.menu/combobox.c
    //GList *boxitems = NULL;
    GtkWidget *combo;
    char item;

    combo = gtk_combo_box_text_new();
    //gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, "-- Select game mode --");
    /*2 player mode*/
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[0]);
    g_signal_connect(two_p, "clicked", G_CALLBACK(two_p_mode), NULL);
    /*1 player - ai mode*/
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[1]);
    g_signal_connect(ai, "clicked", G_CALLBACK(ai_mode), NULL);
    /*1 player - ml easy mode*/
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[2]);
    g_signal_connect(ml_easy, "clicked", G_CALLBACK(ml_ez_mode), NULL);
    /*1 player - ml hard mode*/
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[3]);
    g_signal_connect(ml_hard, "clicked", G_CALLBACK(ml_hard_mode), NULL);   

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    g_signal_connect(combo, "clicked", G_CALLBACK(print_home_button),NULL);
    gtk_grid_attach(GTK_GRID(grid), combo, 0,1,16,1);
    
/*
    two_p = gtk_button_new_with_label(mode[0]);
    g_signal_connect(two_p, "clicked", G_CALLBACK(two_p_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid), two_p, 0,1,4,1);
    gtk_widget_set_sensitive(two_p, FALSE); //selected by default
    ai = gtk_button_new_with_label(mode[1]);
    g_signal_connect(ai, "clicked", G_CALLBACK(ai_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid), ai, 4,1,4,1);
    ml_easy = gtk_button_new_with_label(mode[2]);
    g_signal_connect(ml_easy, "clicked", G_CALLBACK(ml_ez_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid), ml_easy, 8,1,4,1);
    ml_hard = gtk_button_new_with_label(mode[3]);
    g_signal_connect(ml_hard, "clicked", G_CALLBACK(ml_hard_mode),NULL);
    gtk_grid_attach(GTK_GRID(grid), ml_hard, 12,1,4,1);
*/

    char str_int[5];
    char currentPlayer[15];
    strcpy(currentPlayer, playerName[0]);
    xScore = gtk_button_new_with_label(strcat(strcat(currentPlayer,": "),itoa(x_win,str_int,10)));
    gtk_widget_set_sensitive(xScore, FALSE);
    gtk_grid_attach(GTK_GRID(grid), xScore, 0,2,2,1);
    strcpy(currentPlayer, playerName[1]);
    oScore = gtk_button_new_with_label(strcat(strcat(currentPlayer,": "),itoa(o_win,str_int,10)));
    gtk_widget_set_sensitive(oScore, FALSE);
    gtk_grid_attach(GTK_GRID(grid), oScore, 2,2,2,1);
    strcpy(currentPlayer, "AI");
    aiScore = gtk_button_new_with_label(strcat(strcat(currentPlayer,": "),itoa(ai_win,str_int,10)));
    gtk_widget_set_sensitive(aiScore, FALSE);
    gtk_grid_attach(GTK_GRID(grid), aiScore, 4,2,4,1);
    strcpy(currentPlayer, "Easy-Bot");
    easyScore = gtk_button_new_with_label(strcat(strcat(currentPlayer,": "),itoa(easy_win,str_int,10)));
    gtk_widget_set_sensitive(easyScore, FALSE);
    gtk_grid_attach(GTK_GRID(grid), easyScore, 8,2,4,1);
    strcpy(currentPlayer, "Hard-Bot");
    hardScore = gtk_button_new_with_label(strcat(strcat(currentPlayer,": "),itoa(hard_win,str_int,10)));
    gtk_widget_set_sensitive(hardScore, FALSE);
    gtk_grid_attach(GTK_GRID(grid), hardScore, 12,2,4,1);


    quit = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped (quit, "clicked", G_CALLBACK (gtk_window_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), quit, 0,7,1,1);
    
    credits = gtk_button_new_with_label("Credits");
    g_signal_connect_swapped (credits, "clicked", G_CALLBACK (print_credits), window);
    gtk_grid_attach(GTK_GRID(grid), credits, 15,7,1,1);

    resetButton = gtk_button_new_with_label("RESET");
    g_signal_connect_swapped(resetButton,"clicked",G_CALLBACK(resetBoard),NULL);
    gtk_grid_attach(GTK_GRID(grid),resetButton,15,3,1,1);

    printBoard(board);
    tile[0] = board[0][0];
    b00 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b00,"clicked",G_CALLBACK(button00),NULL);
    gtk_grid_attach(GTK_GRID(grid),b00,4,4,1,1);

    tile[0] = board[0][1];
    b01 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b01,"clicked",G_CALLBACK(button01),NULL);
    gtk_grid_attach(GTK_GRID(grid),b01,5,4,1,1);


    tile[0] = board[0][2];
    b02 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b02,"clicked",G_CALLBACK(button02),NULL);
    gtk_grid_attach(GTK_GRID(grid),b02,6,4,1,1);

    tile[0] = board[1][0];
    b10 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b10,"clicked",G_CALLBACK(button10),NULL);
    gtk_grid_attach(GTK_GRID(grid),b10,4,5,1,1);

    tile[0] = board[1][1];
    b11 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b11,"clicked",G_CALLBACK(button11),NULL);
    gtk_grid_attach(GTK_GRID(grid),b11,5,5,1,1);

    tile[0] = board[1][2];
    b12 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b12,"clicked",G_CALLBACK(button12),NULL);
    gtk_grid_attach(GTK_GRID(grid),b12,6,5,1,1);

    tile[0] = board[2][0];
    b20 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b20,"clicked",G_CALLBACK(button20),NULL);
    gtk_grid_attach(GTK_GRID(grid),b20,4,6,1,1);

    tile[0] = board[2][1];
    b21 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b21,"clicked",G_CALLBACK(button21),NULL);
    gtk_grid_attach(GTK_GRID(grid),b21,5,6,1,1);

    tile[0] = board[2][2];
    b22 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b22,"clicked",G_CALLBACK(button22),NULL);
    gtk_grid_attach(GTK_GRID(grid),b22,6,6,1,1);




    //disableTTT(b00,b01,b02,b10,b11,b12,b20,b21,b22);

    gtk_widget_show(window);
    
}

static void print_home_button(GtkWidget *widget, gpointer data){
    g_print("Home\n");
}

// /*menu to select mode*/
// //https://www.cc.gatech.edu/data_files/public/doc/gtk/tutorial/gtk_tut-14.html
// void menu(GtkApplication *menu, gpointer data){
//     GtkWidget *window;
//     GtkWidget *menu;
//     GtkWidget *menu_items;

//     /*create new window*/
//     window = gtk_application_window_new(menu);
//     gtk_window_set_title(GTK_WINDOW(window), "SELECT GAME MODE");

//     menu = gtk_menu_new();
//     g_menu_append_item(GMenu menu);

// }


static void disableTTT(){
    gtk_widget_set_sensitive(b00, FALSE);
    gtk_widget_set_sensitive(b01, FALSE);
    gtk_widget_set_sensitive(b02, FALSE);
    gtk_widget_set_sensitive(b10, FALSE);
    gtk_widget_set_sensitive(b11, FALSE);
    gtk_widget_set_sensitive(b12, FALSE);
    gtk_widget_set_sensitive(b20, FALSE);
    gtk_widget_set_sensitive(b21, FALSE);
    gtk_widget_set_sensitive(b22, FALSE);
}
static void enableTTT(){
    gtk_widget_set_sensitive(b00, TRUE);
    gtk_widget_set_sensitive(b01, TRUE);
    gtk_widget_set_sensitive(b02, TRUE);
    gtk_widget_set_sensitive(b10, TRUE);
    gtk_widget_set_sensitive(b11, TRUE);
    gtk_widget_set_sensitive(b12, TRUE);
    gtk_widget_set_sensitive(b20, TRUE);
    gtk_widget_set_sensitive(b21, TRUE);
    gtk_widget_set_sensitive(b22, TRUE);
}

void updateBoard(int x, int y,GtkWidget *widget, gpointer button){
    printf("row %d col %d\n",x,y);

    if (board[x][y]==' '){
        board[x][y]=PLAYER[turn%2];
        turn += 1;
        gtk_widget_set_sensitive(button, FALSE);
    }
    GtkButton *change_button = (GtkButton *) button;
    tile[0] = board[x][y];
    gtk_button_set_label (change_button, tile);
    printBoard(board);
    
    if (checkFreeSpaces()==0 && !win()){
        //dialog msg for draw + distable TTT
        GtkWidget *drawDialog;
        drawDialog = gtk_message_dialog_new (GTK_WINDOW(widget),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "DRAW !");
        gtk_window_set_title(GTK_WINDOW(drawDialog), "PM Tic-Tac-Toe Project");
        //gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (drawDialog),"message");
        g_signal_connect (drawDialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
        gtk_widget_show (drawDialog);

        disableTTT();
    }
    if (win()){
        //dialog msg for win + disableTTT 
        //*NOTE: make new game button(sensitive false default + hide)
        GtkWidget *winDialog;
        winDialog = gtk_message_dialog_new (GTK_WINDOW(widget),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "WINNER: %s !",playerName[(turn-1)%2]);
        gtk_window_set_title(GTK_WINDOW(winDialog), "PM Tic-Tac-Toe Project");
        //gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (winDialog),"message");
        g_signal_connect (winDialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
        gtk_widget_show (winDialog);

        //add win
        if ((turn-1)%2==0){
            x_win+=1;
            change_button = (GtkButton *) xScore;
            char str_int[5];
            char currentPlayer[15];
            strcpy(currentPlayer, playerName[0]);
            gtk_button_set_label (change_button, (strcat(strcat(currentPlayer,": "),itoa(x_win,str_int,10))));
        }
        else if ((turn-1)%2==1){
            o_win+=1;
            change_button = (GtkButton *) oScore;
            char str_int[5];
            char currentPlayer[15];
            strcpy(currentPlayer, playerName[1]);
            gtk_button_set_label (change_button,(strcat(strcat(currentPlayer,": "),itoa(o_win,str_int,10))));
        }
        

        disableTTT();
    }

    //if mode is not 2P ----> need to do checkwin and checkdraw again
    if (currentMode!=0){
        if (currentMode==1){
            //GET COORD FROM AI.h
            //coord = output from ai.h
        }
        else if (currentMode==2){
            //GET COORD FROM ML.h for ez mode
            //coord = output from ml.h
        }
        else if (currentMode==3){
            //coord = output from ml.h
        }
        //if coord == 00, update board, update tile, disable b00
        //if.....
    }
}

static void two_p_mode(GtkWidget *widget, gpointer data){
    resetBoard();
    gtk_widget_set_sensitive(two_p, FALSE);
    gtk_widget_set_sensitive(ai, TRUE);
    gtk_widget_set_sensitive(ml_easy, TRUE);
    gtk_widget_set_sensitive(ml_hard, TRUE);
}
static void ai_mode(GtkWidget *widget, gpointer data){
    resetBoard();
    gtk_widget_set_sensitive(two_p, TRUE);
    gtk_widget_set_sensitive(ai, FALSE);
    gtk_widget_set_sensitive(ml_easy, TRUE);
    gtk_widget_set_sensitive(ml_hard, TRUE);
}
static void ml_ez_mode(GtkWidget *widget, gpointer data){
    resetBoard();
    gtk_widget_set_sensitive(two_p, TRUE);
    gtk_widget_set_sensitive(ai, TRUE);
    gtk_widget_set_sensitive(ml_easy, FALSE);
    gtk_widget_set_sensitive(ml_hard, TRUE);
}
static void ml_hard_mode(GtkWidget *widget, gpointer data){
    resetBoard();
    gtk_widget_set_sensitive(two_p, TRUE);
    gtk_widget_set_sensitive(ai, TRUE);
    gtk_widget_set_sensitive(ml_easy, TRUE);
    gtk_widget_set_sensitive(ml_hard, FALSE);
}

static void button00(GtkWidget *widget, gpointer data){
   updateBoard(0,0,widget,data);
}

static void button01(GtkWidget *widget, gpointer data){
    updateBoard(0,1,widget,data);
}
static void button02(GtkWidget *widget, gpointer data){
    updateBoard(0,2,widget,data);
}
static void button10(GtkWidget *widget, gpointer data){
    updateBoard(1,0,widget,data);
}
static void button11(GtkWidget *widget, gpointer data){
    updateBoard(1,1,widget,data);
}
static void button12(GtkWidget *widget, gpointer data){
    updateBoard(1,2,widget,data);
}
static void button20(GtkWidget *widget, gpointer data){
    updateBoard(2,0,widget,data);
}
static void button21(GtkWidget *widget, gpointer data){
    updateBoard(2,1,widget,data);
}
static void button22(GtkWidget *widget, gpointer data){
    updateBoard(2,2,widget,data);
}
static void print_credits(GtkWidget *widget, gpointer data){
    g_print("credits\n");

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new (GTK_WINDOW(widget),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Done By:");
    gtk_window_set_title(GTK_WINDOW(dialog), "PM Tic-Tac-Toe Project");
    gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),"GROUP 5:\n[2202122]\tLIEW JING DE BENJAMIN\n[2200754]\tJAVIER NG WEI CHENG\n[2201291]\tNEAM HENG CHONG, TIMOTHY\n[2203393]\tTAN JIA WEN\n[2202666]\tCHER GEK TENG");
    g_signal_connect (dialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
    gtk_widget_show (dialog);
}