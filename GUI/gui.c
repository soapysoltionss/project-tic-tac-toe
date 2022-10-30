#include <stdio.h>
<<<<<<< HEAD

=======
#include <gtk/gtk.h>

static char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
static char tile[2] = " \0";
static int currentMode = 0; //0->2P mode, 1->AI mode...

const char mode[2][20]={"2-Player Mode","1-Player Mode (AI)"};
const char PLAYER[2] = {'X','O'};
int turn = 0; //for turn counter (reset on board reset) + turn%2 = player


void printBoard();
void resetBoard();
int checkFreeSpaces();
void updateBoard(int x, int y, gpointer button);

static void activate (GtkApplication *app, gpointer data);
static void print_home_button(GtkWidget *widget, gpointer data);
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
static void disableTTT(gpointer b00,gpointer b01,gpointer b02,gpointer b10,gpointer b11,gpointer b12,gpointer b20,gpointer b21,gpointer b22);


int main(int argc, char **argv){
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.gtk.example",G_APPLICATION_DEFAULT_FLAGS);
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


//GTK GUI FUNCTIONS
static void activate (GtkApplication *app, gpointer data){
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *home, *quit, *credits;
    GtkWidget *b00,*b01,*b02,*b10,*b11,*b12,*b20,*b21,*b22;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Tic-Tac-Toe");

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window),grid);

    
    //https://stackoverflow.com/questions/16630528/trying-to-populate-a-gtkcombobox-with-model-in-c
    GtkWidget *combo;
    char item;
    combo = gtk_combo_box_new();
    //gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, "A");
    //gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, "B");
    //gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, "C");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 1);
    g_signal_connect(combo, "clicked", G_CALLBACK(print_home_button),NULL);
    gtk_grid_attach(GTK_GRID(grid), combo, 0,0,1,1);
    
    /*home = gtk_button_new_with_label("HOME");
    g_signal_connect(home, "clicked", G_CALLBACK(print_home_button),NULL);
    gtk_grid_attach(GTK_GRID(grid), home, 0,0,1,1);
    */

    quit = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped (quit, "clicked", G_CALLBACK (gtk_window_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), quit, 0,5,1,1);
    
    credits = gtk_button_new_with_label("Credits");
    g_signal_connect_swapped (credits, "clicked", G_CALLBACK (print_credits), window);
    gtk_grid_attach(GTK_GRID(grid), credits, 13,5,1,1);

    printBoard(board);
    tile[0] = board[0][0];
    b00 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b00,"clicked",G_CALLBACK(button00),NULL);
    gtk_grid_attach(GTK_GRID(grid),b00,10,2,1,1);

    tile[0] = board[0][1];
    b01 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b01,"clicked",G_CALLBACK(button01),NULL);
    gtk_grid_attach(GTK_GRID(grid),b01,11,2,1,1);


    tile[0] = board[0][2];
    b02 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b02,"clicked",G_CALLBACK(button02),NULL);
    gtk_grid_attach(GTK_GRID(grid),b02,12,2,1,1);

    tile[0] = board[1][0];
    b10 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b10,"clicked",G_CALLBACK(button10),NULL);
    gtk_grid_attach(GTK_GRID(grid),b10,10,3,1,1);

    tile[0] = board[1][1];
    b11 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b11,"clicked",G_CALLBACK(button11),NULL);
    gtk_grid_attach(GTK_GRID(grid),b11,11,3,1,1);

    tile[0] = board[1][2];
    b12 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b12,"clicked",G_CALLBACK(button12),NULL);
    gtk_grid_attach(GTK_GRID(grid),b12,12,3,1,1);

    tile[0] = board[2][0];
    b20 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b20,"clicked",G_CALLBACK(button20),NULL);
    gtk_grid_attach(GTK_GRID(grid),b20,10,4,1,1);

    tile[0] = board[2][1];
    b21 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b21,"clicked",G_CALLBACK(button21),NULL);
    gtk_grid_attach(GTK_GRID(grid),b21,11,4,1,1);

    tile[0] = board[2][2];
    b22 = gtk_button_new_with_label(tile);
    g_signal_connect_swapped(b22,"clicked",G_CALLBACK(button22),NULL);
    gtk_grid_attach(GTK_GRID(grid),b22,12,4,1,1);




    //disableTTT(b00,b01,b02,b10,b11,b12,b20,b21,b22);

    gtk_widget_show(window);
    
}


static void print_home_button(GtkWidget *widget, gpointer data){
    g_print("Home\n");
}

static void disableTTT(gpointer b00,gpointer b01,gpointer b02,gpointer b10,gpointer b11,gpointer b12,gpointer b20,gpointer b21,gpointer b22){
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

void updateBoard(int x, int y, gpointer button){
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
}

static void button00(GtkWidget *widget, gpointer data){
   updateBoard(0,0,data);
}

static void button01(GtkWidget *widget, gpointer data){
    updateBoard(0,1,data);
}
static void button02(GtkWidget *widget, gpointer data){
    updateBoard(0,2,data);
}
static void button10(GtkWidget *widget, gpointer data){
    updateBoard(1,0,data);
}
static void button11(GtkWidget *widget, gpointer data){
    updateBoard(1,1,data);
}
static void button12(GtkWidget *widget, gpointer data){
    updateBoard(1,2,data);
}
static void button20(GtkWidget *widget, gpointer data){
    updateBoard(2,0,data);
}
static void button21(GtkWidget *widget, gpointer data){
    updateBoard(2,1,data);
}
static void button22(GtkWidget *widget, gpointer data){
    updateBoard(2,2,data);
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
    gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),"Ben\nppl\n");
    g_signal_connect (dialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
    gtk_widget_show (dialog);
}
>>>>>>> e204dbe57f1f2dc22baa58ef6721985377e368c6
