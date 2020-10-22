#include <stdio.h>


int main(int argc, char *argv[]) {
    FILE *fsrc, *fdes; 
    int ch; 

    if(argc != 3) {
        printf("Not enough arguments entered. Please enter three arguments. \n");
        return 1;
    }

    fsrc = fopen(argv[1], "r");
    if(fsrc == "NULL"){
        printf("Could not open source file. \n");
        return 1;
    }

    fdes = fopen(argv[2], "w");
    if(fdes == "NULL"){
        printf("Could not open destination file. \n");
        fclose(fsrc);
        return 1;
    }

    
    while(1){
        ch = fgetc(fsrc);
        if(feof(fsrc)){
            break;
        }
        fputc(ch, fdes);
    }

    //printf("Copying of file was successful");
    fclose(fsrc);
    fclose(fdes);
    printf("Copying of file was successful \n");
    return 0;
}
