/* Include Libraries */
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h> // include gtk for gui
#include "../tictactoe.h"// include header file to link .c files


/* Create Board */
static char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
static char tile[2] = " \0"; // used to input button label (char[] type)

/* Game Difficulty Modes */
static int currentMode = 0; //0->2P mode, 1->AI mode, 2-> ML mode
static const char mode[4][25]={"2-Player Mode",
                        "AI-Bot Mode",
                        "Easy-Bot Mode"};

/* Player Variables */
static const char PLAYER[2] = {'X','O'}; // Player Icon
static char playerName[2][15] = {"Player 1","Player 2"}; // Player Name
static int turn = 0; // turn counter. turn%2 = current player.

/* Score Counters */
static int x_win, o_win, ai_win, easy_win;

/* GUI Widgets */
// set to global for functions to be able to access
static GtkWidget *b00,*b01,*b02,*b10,*b11,*b12,*b20,*b21,*b22; // tic-tac-toe buttons
static GtkWidget *two_p, *ai, *ml_easy; // Game Mode buttons
static GtkWidget *xScore,*oScore,*aiScore,*easyScore; // Score board buttons


/* Functions */
static void printBoard(); // Displays Board in Terminal Console
static int checkFreeSpaces(); // Checks for Free spots on the Board
static bool win(); // Checks if there is a Winner
/* Update Tic-Tac-Toe Board Functions */
static void resetBoard(); // Restarts Tic-Tac-Toe Board
static void updateBoard(int x, int y,GtkWidget *widget, gpointer button); // Updates board based on gui input
static void disableTTT(); // Disable Tic-Tac-Toe Board
static void enableTTT(); // Enable Tic-Tac-Toe Board
/* GUI Activate Application Functions */
static void activate (GtkApplication *app, gpointer data);
/* GUI Button Callback Functions */
static void print_home_button(GtkWidget *widget, gpointer data); //TROUBLESHOOTING !
static void print_home_button(GtkWidget *widget, gpointer data){
    g_print("Home\n");
}
/* GUI Mode Buttons Callback Functions */
static void two_p_mode(GtkWidget *widget, gpointer data);
static void ai_mode(GtkWidget *widget, gpointer data);
static void ml_ez_mode(GtkWidget *widget, gpointer data);
/* GUI Tic-Tac-Toe Board Buttons Callback Functions */
static void button00(GtkWidget *widget, gpointer data);
static void button01(GtkWidget *widget, gpointer data);
static void button02(GtkWidget *widget, gpointer data);
static void button10(GtkWidget *widget, gpointer data);
static void button11(GtkWidget *widget, gpointer data);
static void button12(GtkWidget *widget, gpointer data);
static void button20(GtkWidget *widget, gpointer data);
static void button21(GtkWidget *widget, gpointer data);
static void button22(GtkWidget *widget, gpointer data);
/* GUI Credits Button Callback Function */
static void print_credits(GtkWidget *widget, gpointer data);


/* Created for Ai.c */
struct Move
{
	int row, col;
};


/* MAIN -> calls gui application */
int main(int argc, char **argv){
    GtkApplication *app;
    int status;

    app = gtk_application_new("TIC.TAC.TOE",G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status = g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);

    return status;
}

/* GUI */
static void activate (GtkApplication *app, gpointer data){
    /* Gtk Widgets */
    GtkWidget *window; // create gtk window
    GtkWidget *grid; // create gtk grid
    GtkWidget *menu, *quit, *credits, *resetButton, *txtButton; // create gtk buttons
    //GtkWidget *b00,*b01,*b02,*b10,*b11,*b12,*b20,*b21,*b22;

    /* Create GTK Window */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Tic-Tac-Toe");
    /* Create GTK Grid */
    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window),grid);

    /* Create GTK Buttons & Position them on the Grid */
    /* Top Row */
    txtButton = gtk_button_new_with_label("TIC-TAC-TOE");
    gtk_widget_set_sensitive(txtButton, FALSE);
    gtk_grid_attach(GTK_GRID(grid), txtButton, 0,0,14,1);
    txtButton = gtk_button_new_with_label("SETTING");
    //g_signal_connect(txtButton, "clicked", G_CALLBACK(settings), NULL);
    //g_signal_connect(msgButton, "clicked", G_CALLBACK(print_home_button),NULL);
    gtk_grid_attach(GTK_GRID(grid), txtButton, 14,0,2,1);

/*COMBO BOX ATTEMPT
    //https://stackoverflow.com/questions/16630528/trying-to-populate-a-gtkcombobox-with-model-in-c
    //https://github.com/steshaw/gtk-examples/blob/master/ch05.menu/combobox.c
    //GList *boxitems = NULL;
    GtkWidget *combo;
    char item;

    combo = gtk_combo_box_text_new();
    //2 player mode
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[0]);
    g_signal_connect(two_p, "clicked", G_CALLBACK(two_p_mode), NULL);
    //1 player - ai mode
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[1]);
    g_signal_connect(ai, "clicked", G_CALLBACK(ai_mode), NULL);
    //1 player - ml easy mode
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, mode[2]);
    g_signal_connect(ml_easy, "clicked", G_CALLBACK(ml_ez_mode), NULL);


    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    g_signal_connect(combo, "clicked", G_CALLBACK(print_home_button),NULL);
    gtk_grid_attach(GTK_GRID(grid), combo, 0,1,16,1);
*/


    /* Game Mode Row */
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


    /* ScoreBoard Row */
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


    /* Tic-Tac-Toe Board */
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


    /* Miscellaneous Buttons */
    quit = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped (quit, "clicked", G_CALLBACK (gtk_window_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), quit, 0,7,1,1);

    credits = gtk_button_new_with_label("Credits");
    g_signal_connect_swapped (credits, "clicked", G_CALLBACK (print_credits), window);
    gtk_grid_attach(GTK_GRID(grid), credits, 15,7,1,1);

    resetButton = gtk_button_new_with_label("RESET");
    g_signal_connect_swapped(resetButton,"clicked",G_CALLBACK(resetBoard),NULL);
    gtk_grid_attach(GTK_GRID(grid),resetButton,15,3,1,1);

    /* Display Window */
    gtk_widget_show(window);

}

/* Display Board in Terminal Console */
static void printBoard()
{
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}
/* Checks for Free spots on the Board */
static int checkFreeSpaces(){
    int fs = 9;
    for (int x=0;x<3;x++){
        for (int y=0;y<3;y++){
            if (board[x][y] != ' '){
                fs--;
            }
        }
    }
    return fs; // returns number of free spots
}
/* Restart Tic-Tac-Toe Game */
static void resetBoard(){
    /* Set Board to free spaces */
    for (int x=0;x<3;x++){
        for (int y=0;y<3;y++){
            board[x][y] = ' ';
        }
    }
    /* Reset turn */
    turn=0;
    /* Reset All GUI Tic-Tac-Toe Buttons to free spaces */
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
    /* Enable All GUI Tic-Tac-Toe Buttons */
    enableTTT();
}
/* Checks if there is a Winner */
static bool win(){
    /*  check for ROW WIN
        for loop for every row
        check if column 0, 1, 2 are the same
        if they are they same, then check char,
        check if player or AI won
        else if column are not the same, return 0 */
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1]
        && board[row][1] == board[row][2]) {
             if (board[row][0] == ' ') {
                continue;
            }
            else if (board[row][0] == 'X') {
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
            if (board[0][col] == ' ') {
                continue;
            }
            else if (board[0][col] == 'X') {
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

    /*  check for DIAGONAL WIN in "\" slope
        check if box 0, 4, 8 OR box 3, 4, 6 are the same
        box 0 = [0][0], box 4 = [1][1] , box 8 = [2][2], box 3 = [1][0], box 4 = [1][1], box 6 = [2][0] */
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
    /* check for the DIAGONAL WIN in "/" slope */
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
/* Disable Tic-Tac-Toe Board */
static void disableTTT(){
    /* Set all Tic-Tac-Toe buttons to False */
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
/* Enable Tic-Tac-Toe Board */
static void enableTTT(){
    /* Set all Tic-Tac-Toe buttons to True */
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
/* Update board based on GUI User input callback */
static void updateBoard(int x, int y,GtkWidget *widget, gpointer button){
    int bot_coord[2]; // for ai/ml coordinate
    printf("row %d col %d\n",x,y);

    if (board[x][y]==' '){          // if chosen spot is empty
        board[x][y]=PLAYER[turn%2]; // set X or O
        turn += 1; // increment turn
        gtk_widget_set_sensitive(button, FALSE); // disable spot by setting to False
    }
    tile[0] = board[x][y];
    gtk_button_set_label ((gpointer)button, tile); //updatiupdating button to X or O
    printBoard(board);

    /* DRAW */
    if (checkFreeSpaces()==0 && !win()){
        //dialog msg for draw + distable TTT
        GtkWidget *drawDialog;
        drawDialog = gtk_message_dialog_new (GTK_WINDOW(widget),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "DRAW !");
        gtk_window_set_title(GTK_WINDOW(drawDialog), "PM Tic-Tac-Toe Project");
        g_signal_connect (drawDialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
        gtk_widget_show (drawDialog);

        disableTTT();
    }
    /* Player WIN */
    if (win()){
        //dialog msg for win + distable TTT
        GtkWidget *winDialog;
        winDialog = gtk_message_dialog_new (GTK_WINDOW(widget),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "WINNER: %s !",playerName[(turn-1)%2]);
        gtk_window_set_title(GTK_WINDOW(winDialog), "PM Tic-Tac-Toe Project");
        g_signal_connect (winDialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
        gtk_widget_show (winDialog);

        //add win
        if ((turn-1)%2==0){
            x_win+=1;
            char str_int[5];
            char currentPlayer[15];
            strcpy(currentPlayer, playerName[0]);
            gtk_button_set_label ((gpointer)xScore, (strcat(strcat(currentPlayer,": "),itoa(x_win,str_int,10))));
        }
        else if ((turn-1)%2==1){
            o_win+=1;
            char str_int[5];
            char currentPlayer[15];
            strcpy(currentPlayer, playerName[1]);
            gtk_button_set_label ((gpointer)oScore,(strcat(strcat(currentPlayer,": "),itoa(o_win,str_int,10))));
        }


        disableTTT();
    }




    //if mode is not 2P ----> need to do checkwin and checkdraw again
    if (currentMode!=0){
        if (currentMode==1){
            //GET COORD FROM AI.h
            struct Move bestMove = findNextBestMove(board);
            bot_coord[0]=bestMove.row;
            bot_coord[1]=bestMove.col;
            printf("\nAI ROW: %d AI COL: %d\n", bestMove.row, bestMove.col );
        }
        else if (currentMode==2){
            //GET COORD FROM ML.h for ez mode
            //coord = output from ml.h
        }


        // update Board with AI/ML move
        board[bot_coord[0]][bot_coord[1]] = PLAYER[turn%2];
        turn += 1;
        tile[0] = board[bot_coord[0]][bot_coord[1]];
        if (bot_coord[0]==0 && bot_coord[1]==0){
            gtk_button_set_label ((gpointer)b00, tile);
            gtk_widget_set_sensitive(b00, FALSE);
        }
        if (bot_coord[0]==0 && bot_coord[1]==1){
            gtk_widget_set_sensitive(b01, FALSE);
            gtk_button_set_label ((gpointer)b01, tile);
        }
        if (bot_coord[0]==0 && bot_coord[1]==2){
            gtk_widget_set_sensitive(b02, FALSE);
            gtk_button_set_label ((gpointer)b02, tile);
        }
        if (bot_coord[0]==1 && bot_coord[1]==0){
            gtk_widget_set_sensitive(b10, FALSE);
            gtk_button_set_label ((gpointer)b10, tile);
        }
        if (bot_coord[0]==1 && bot_coord[1]==1){
            gtk_widget_set_sensitive(b11, FALSE);
            gtk_button_set_label ((gpointer)b11, tile);
        }
        if (bot_coord[0]==1 && bot_coord[1]==2){
            gtk_widget_set_sensitive(b12, FALSE);
            gtk_button_set_label ((gpointer)b12, tile);
        }
        if (bot_coord[0]==2 && bot_coord[1]==0){
            gtk_widget_set_sensitive(b20, FALSE);
            gtk_button_set_label ((gpointer)b20, tile);
        }
        if (bot_coord[0]==2 && bot_coord[1]==1){
            gtk_widget_set_sensitive(b21, FALSE);
            gtk_button_set_label ((gpointer)b21, tile);
        }
        if (bot_coord[0]==2 && bot_coord[1]==2){
            gtk_widget_set_sensitive(b22, FALSE);
            gtk_button_set_label ((gpointer)b22, tile);
        }

        if (win()){
            //dialog msg for win + disableTTT
            //*NOTE: make new game button(sensitive false default + hide)
            GtkWidget *winDialog;
            winDialog = gtk_message_dialog_new (GTK_WINDOW(widget),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "WINNER: %s !","AI");
            gtk_window_set_title(GTK_WINDOW(winDialog), "PM Tic-Tac-Toe Project");
            g_signal_connect (winDialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
            gtk_widget_show (winDialog);

            //add win
            if ((turn-1)%2==0){
                x_win+=1;
                char str_int[5];
                char currentPlayer[15];
                strcpy(currentPlayer, playerName[0]);
                gtk_button_set_label ((gpointer)xScore, (strcat(strcat(currentPlayer,": "),itoa(x_win,str_int,10))));
            }
            else if ((turn-1)%2==1){
                ai_win+=1;
                char str_int[5];
                char currentPlayer[15];
                strcpy(currentPlayer, "AI");
                gtk_button_set_label ((gpointer)aiScore,(strcat(strcat(currentPlayer,": "),itoa(ai_win,str_int,10))));
            }
            disableTTT();
        }


    printBoard(board);
    }
}

/* Settings attempt
static void print_text(GtkWidget *widget, gint response_id, gpointer data){
    GtkEntry *entry = data;
    printf("%s", gtk_entry_get_text(entry));
    gtk_widget_destroy(widget); // Close dialog
}

static void settings(GtkWidget *widget, gpointer data){
    GtkWindow *window = data;
    GtkLabel *label;
    GtkEntry *textbox;
    GtkWidget *dialog, *saveButton;

    //window = gtk_application_window_new(app);
    //gtk_window_set_title(GTK_WINDOW(window), "Edit profile");
    dialog = gtk_message_dialog_new("User profile",
                                    window,
                                    GTK_MESSAGE_INFO,
                                    GTK_DIALOG_MODAL,
                                    NULL);


    label = gtk_label_new("Username: ");
    textbox = gtk_entry_new();
    gtk_entry_set_text(textbox, "Enter username here");
    //const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry));

    gtk_widget_show(dialog);
    g_signal_connect(GTK_DIALOG (dialog), "response", G_CALLBACK (print_text), textbox);
}

static void settingsActivate(GtkApplication *app, gpointer data){
    GtkWidget *window, *button, *entry;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "User profile");

    button = gtk_button_new_with_label("Save");
    g_signal_connect(button, "clicked", G_CALLBACK(settings), NULL);
    
    gtk_widget_show(window);
}
*/

/* Callback to Change Mode */
static void two_p_mode(GtkWidget *widget, gpointer data){
    resetBoard(); // Reset Board
    gtk_widget_set_sensitive(two_p, FALSE); // Set current mode button to False
    gtk_widget_set_sensitive(ai, TRUE);
    gtk_widget_set_sensitive(ml_easy, TRUE);
    currentMode=0; // Update Current Mode value
}
static void ai_mode(GtkWidget *widget, gpointer data){
    resetBoard(); // Reset Board
    gtk_widget_set_sensitive(two_p, TRUE);
    gtk_widget_set_sensitive(ai, FALSE); // Set current mode button to False
    gtk_widget_set_sensitive(ml_easy, TRUE);
    currentMode=1; // Update Current Mode value
}
static void ml_ez_mode(GtkWidget *widget, gpointer data){
    resetBoard(); // Reset Board
    gtk_widget_set_sensitive(two_p, TRUE);
    gtk_widget_set_sensitive(ai, TRUE);
    gtk_widget_set_sensitive(ml_easy, FALSE); // Set current mode button to False
    currentMode=2; // Update Current Mode value
}

/* Tic-Tac-Toe Buttons Callback to update Board */
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
/* Display Window to show Project Credits */
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