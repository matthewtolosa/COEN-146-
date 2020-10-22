#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    char buf;

    // first file is to read in its contents
    int src = open(argv[1], O_RDWR);
    if (src == -1) {
        printf("Cannot open file \n");
        exit(0);
    }

    // create a file if one doesn't exist or prepare to write to it
    int dest = open(argv[2], O_WRONLY | O_CREAT, 0641);
    if(dest == -1) {
        printf("Destination file error \n");
        exit(0);
    }

    // write to the file until we reach the end of source file
    while((read(src, &buf, 1)) > 0) {
        write(dest, &buf, 1 );
    }
    //printf(" Files are sucessfully copied \n");
    close(src);
    close(dest);
    printf(" Files are sucessfully copied \n");

    return 0;
}
