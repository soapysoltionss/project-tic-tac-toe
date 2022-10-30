#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *ptr_readFile;
    char con[1000000];
    
// Create file pointers
    ptr_readFile = fopen("dataset/tic-tac-toe.data", "r");

    if (!ptr_readFile){
        perror("File Opening Failed");
        return EXIT_FAILURE;
    }
    while(fgets (con, 1000000, ptr_readFile) != NULL) {

        printf("%s", con);
    }
    
    fclose(ptr_readFile);

    return EXIT_SUCCESS;
    
}