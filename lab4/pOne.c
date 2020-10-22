/*Matthew Tolosa 
10/16/20 
This program serves as a TCP server that accepts and responds to multiple client connection requests for file transfer 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//Peer 1

int main(){
        int answer;
        while(1){
                printf("Sending(1) or receiving(2) file?, or leave(3): ");
                scanf("%d", &answer);
                //Acts like server UDP transfer
                if (answer == 1) {
                        int speerid;
                        char inputfile[100];
                        char sbuff[1024];
                        struct sockaddr_in recAddr, sendAddr; //server address for receiving message from requesting peer, and sending message back to requesting peer
                        socklen_t addrLen = sizeof(struct sockaddr);

                        if ((speerid = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                                perror("Failure to create datagram socket\n");
                                exit(1);
                        }
                        //Setup the server address to bind to using socket addressing structure
                        recAddr.sin_family = AF_INET;
                        recAddr.sin_port = htons(5002);
                        recAddr.sin_addr.s_addr = INADDR_ANY;

                        //Set address/port of receiving peer(this) for socket descriptor
                        if ((bind(speerid, (struct sockaddr *)&recAddr, sizeof(struct sockaddr))) < 0) {
                                perror("Failure to bind server address to endpoint socket");
                                exit(1);
                        }
                        FILE *fp1;
                        int scount, scount2;
                        while (1) {
                                printf("Waiting for other peer...\n");
                                scount = recvfrom(speerid, inputfile, sizeof(inputfile), 0, (struct sockaddr *)&sendAddr, &addrLen);
                                printf("Connection made\n");
                                inputfile[scount] = '\0';
                                printf("Peer requesting: %s\n", inputfile);
                                fp1 = fopen(inputfile, "r");
                                if (fp1 == NULL) {
                                        printf("Inputted file could not be opened\n");
                                        exit(1);
                                }
                                printf("File %s opened correctly\n", inputfile);
                                scount2 = fread(&sbuff, sizeof(char), sizeof(sbuff), fp1);
                                sbuff[scount2] = '\0';
                                printf("Sending message: %s\n", sbuff);
                                sendto(speerid, sbuff, scount2, 0, (struct sockaddr*)&sendAddr, sizeof(struct sockaddr));
                                fclose(fp1);
                                break;
                        }
                        close(speerid);
                }
                //Acts like client UDP transfer
                else if (answer == 2) {
                        int rpeerid;
                        char filename[100];
                        char rbuff[1024];
                        struct sockaddr_in targetAddr;
                        socklen_t addrLen = sizeof(struct sockaddr);
                        struct hostent *host;
                        host = (struct hostent *)gethostbyname("localhost");

                        //Open a socket for this peer to receive data
                        if((rpeerid = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                                perror("Failure to setup peer socket\n");
                                exit(1);
                        }
                        //Set up a receiving address to receive a file from another peer using socket addressing structure
                        targetAddr.sin_family = AF_INET;
                        targetAddr.sin_port = htons(5001); //Target port assigned 5001
                        targetAddr.sin_addr = *((struct in_addr *)host->h_addr);

                        //Socket creation successful, ready to receive messages
                        FILE *fp2;
                        int rcount;
                        int check;
                        char outputfile[100];
                        while(1) {
                                printf("Requesting file: ");
                                scanf("%s", filename);
                                sendto(rpeerid, filename, strlen(filename), 0, (struct sockaddr *)&targetAddr, sizeof(struct sockaddr));
                                //Receive copy of file name requested back
                                //Store into destination file
                                check = recvfrom(rpeerid, rbuff, sizeof(rbuff), 0, (struct sockaddr *)&targetAddr, &addrLen);
                                printf("Bytes received: %d\n", check);
                                if (check < 1) {
                                        printf("Receiving file unsuccessful\n");
                                        exit(1);
                                }
                                printf("File to copy data to?: ");
                                scanf("%s", outputfile);
                                fp2 = fopen(outputfile, "w");
                                if (fp2 == NULL) {
                                        perror("Destination could not be verified\n");
                                        exit(1);
                                }
                                fwrite(&rbuff, sizeof(char), check, fp2);
                                printf("File received successfully\n");
                                fclose(fp2);
                                break;

                        }
                        close(rpeerid);
                }
                else {
                        printf("Leaving P2P connections\n");
                        return 0;
                }
        }
}