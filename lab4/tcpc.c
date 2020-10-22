/*Matthew Tolosa
Lab 4 
10/16/20 
This program serves as a TCP client that accepts and responds to multiple client connection requests for file transfer 
*/
//Client Side

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int main() {

        //Create client side socket for communication with server
        int sockid; //socket id
        struct sockaddr_in servAddr;
        struct hostent *host;

        //Open socket, if successful, returns a descriptor associated with an endpoint
        if ((sockid = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("Failure to setup an endpoint socket");
                exit(1);
        }

        host = (struct hostent *)gethostbyname("localhost");

        //Define the characteristics (address and port numbers) of server side program
        //Client side sends data to the server side specified by port # and IP address
        //Set the server address to send using socket addressing structure
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(5000);
        servAddr.sin_addr = *((struct in_addr *)host->h_addr);

        //Client prepared for communication requesting with server
        //Connect and accept between client to server happens concurrently
        //Connect to server
        if (connect(sockid, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)) < 0) {
                perror("Failure to connect to the server");
                exit(1);
        }

        //After connection established, communication able to execute
        char filename[100]; //char array for inputted file name
        char destfile[100]; //char array for destination of file contents
        char rbuff[1024]; //receiving buffer
        FILE *fp;
        int total_size = 0;
        int count = 0;
        int length = 0;
        printf("Client: Enter a file to send to server: ");
        scanf("%s", filename); //sending buffer
        if ((send(sockid, filename, strlen(filename), 0)) < 0) {
                perror("Failure to send message\n");
                exit(1);
        }
        //Waits for response back from server
        printf("Receiving...\n");
        while(1) {
                count = recv(sockid, rbuff, sizeof(rbuff), 0);
                if (count > 0) {
                        printf("bytes: %d\n", count);
                        length = count;
                        rbuff[count] = '\0';
                }
                else if (count == 0) {
                        printf("Connection closed\n");
                        break;
                }
                else {
                        printf("Receiving failed\n");
                        break;
                }
        }
        //Close socket after done communicating with server
        int status;
        status = close(sockid);
        if (status == 0) {
                printf("Socket closed successfully\n");
        }
        printf("Server: Sent message: %s\n", rbuff);
        printf("File to save message to?: ");
        scanf("%s", destfile);
        fp = fopen(destfile, "w");
        if (fp == NULL) {
                perror("Failure to open destination file\n");
                exit(1);
        }
        printf("Destination file opened correctly\n");
        fwrite(&rbuff, sizeof(char), length, fp);
        printf("Contents stored in destination file\n");
        fclose(fp);
        return 0;
}


