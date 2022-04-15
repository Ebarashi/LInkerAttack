#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 8196
#define PORT 8080
#define SA struct sockaddr
   
// Function designed for chat between client and server.
void acceptCon(int sockfd,struct sockaddr_in * cli, int * len){
    // Accept the data packet from client and verification
    int connfd = accept(sockfd, (SA*)cli, len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
    // Function for chatting between client and server
    recvPassword(connfd,cli,len,sockfd);
}
void recvPassword(int connfd,struct sockaddr_in * cli, int * len,int sockfd)
{
    char buff[MAX];
        bzero(buff, MAX);
        char * con="con";
        write(connfd,con,sizeof(con));
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        fflush(stdout);
        printf("From client: %s\n", buff);
        char *recv="recv";
        write(connfd,recv,sizeof(recv));
        bzero(buff, MAX);
        close(connfd);
        acceptCon(sockfd, &cli,&len);
}
   
// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
    acceptCon(sockfd, &cli,&len);   
    // After chatting close the socket
    close(sockfd);
}