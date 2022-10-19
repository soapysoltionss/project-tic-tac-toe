#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    char con[1000000];
    
// Create file pointers
    fp = fopen("dataset/tic-tac-toe.data", "r");

    if (!fp){
        perror("File Opening Failed");
        return EXIT_FAILURE;
    }
    while(fgets (con, 1000000, fp) != NULL) {

        printf("%s", con);
    }
    
    fclose(fp);

    return EXIT_SUCCESS;
    
}