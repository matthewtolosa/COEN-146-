/*Matthew Tolosa
Lab 4 
10/16/20 
This program serves as a TCP server that accepts and responds to multiple client connection requests for file transfer 
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

void *file_transfer(void *pservid);

int main() {

        //Create server side socket for communication with a requesting client
        int sockid; //socket id
        int connid; //int for the new socket id used for data transfer
        struct sockaddr_in servAddr, clienAddr;
        socklen_t clientsize;

        //Open a TCP socket, if successful, returns a descriptor associated with an endpoint
        if ((sockid = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("Failure to setup an endpoint socket\n");
                exit(1);
        }
        bzero(&servAddr, sizeof(servAddr));

        //Define the characteristics (address and port numbers) of server side program
        //Server side receives data from the port # and IP address (socket)
        //Setup server address to bind using socket addressing structure
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(5000); //server port #
        servAddr.sin_addr.s_addr = INADDR_ANY;

        //Set address/port of server endpoint for socket socket descriptor
        //bind address socket onto server to reserve a port to let server listen and receive messages with the user of the socket
        if ((bind(sockid, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0) {
                perror("Failure to bind server address to the endpoint socket\n");
                exit(1);
        }

        //listen function to instruct TCP to be ready for incomming client connections
        if((listen(sockid, 5)) < 0) {
                perror("Failure to receive connection\n");
                exit(1);
        }

        //listen(socket ID, queue limit (n amount of participants can be queued at a time for a connection))
        //Server prepared for communication with clients
        //Connect and accept between client to server happens concurrently
        //Server accepting to establish a connection with a requesting client, if successful, returns a connection descriptor to the client

        //Problem, server closes before other client in queue is able to go through thread process. Threading works and if server never closed it can receive multiple client requests and have those clients exchange files with the server. But server is unable to stay open for multiple clients nor close with multiple clients since accept is a blocking command so unable to understand how to find the medium of a TCP server being able to handle multiple clients concurrently.

        int server_status, client_status;
        int counter = 0;
        pthread_t thr;
        while (counter < 5) {
                printf("Waiting for connection...\n");
                //accept() is a blocking command
                connid = accept(sockid, (struct sockaddr *)&clienAddr, &clientsize);
                printf("%d\n", connid);
                if (connid == - 1) {
                        perror("Failure to accept connection with client\n");
                        exit(1);
                }
                printf("Connection made with client specified: %d\n", connid);
                //printf("%d\n", counter);
                if((pthread_create(&thr, NULL, file_transfer, (void*)&connid)) != 0) {
                        perror("Failure with creation of thread\n");
                        exit(1);
                }
                pthread_join(thr, NULL);
                counter++;
        }
        server_status = close(sockid);
        if (server_status == 0) {
                printf("Server socket closed successfully\n");
                return 0;
        }
}
void *file_transfer(void *sockd) {
        FILE *fp1;
        int servid = *((int*)sockd); //casting void pointer to int pointer
        int count = 0;
        int check = 0;
        char inputfile[100];
        char outputfile[100];
        char buff[1024];
        bzero(buff, 1024);
        int client_status;

        while(1) {
                printf("Waiting for file from client\n");
                check = recv(servid, inputfile, 100, 0);
                if (count > 0) {
                        printf("Client sent filename: %s\n", inputfile);
                }
                else if (count == 0) {
                        break;
                }
                else {
                        printf("Receiving failed\n");
                        break;
                }
        }
        fp1 = fopen(inputfile, "r");
        if (fp1 == NULL) {
                perror("Failure to open received file\n");
                exit(1);
        }
        printf("%s opened correctly\n", inputfile);
        if((count = fread(&buff, sizeof(char), sizeof(buff), fp1)) < 0) {
                perror("Failure to read file\n");
                exit(1);
        }
        printf("File contains: %s", buff);
        send(servid, buff, count, 0);
        fclose(fp1);
        client_status = close(servid);
        if (client_status == 0) {
                printf("Client socket closed successfully\n");
        }
        printf("Thread complete with client: %d\n", servid);
        return NULL;
}



