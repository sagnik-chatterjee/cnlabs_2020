#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500 
#define PORT 8080

int main()
{
    int sockfd,len;
    struct sockaddr_in address;
    struct tm *timeinfo;

    int result ;
    char *reply;
   
   int hour,mins,sec,pid;
    //int pid;
    //create socket for client 
    sockfd= socket(AF_INET,SOCK_STREAM,0);

    //anme the socket as with the server 
    address.sin_family= AF_INET;
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    address.sin_port= 8080;
    len=sizeof(address);
    

    //cconnecting the socket to the server's socket 
    result = connect(sockfd,(struct sockaddr *)&address,len);

    if(result==-1){
        printf("[STATUS] Error connecting to the server.");
        exit(0);
    }

    //now read/write via sockfd
    
    printf("[STATUS] Sending request to get the time and pid \n");
    read(sockfd,&hour,1);
    read(sockfd,&mins,1);
    read(sockfd,&sec,1);
    
    read(sockfd,timeinfo,sizeof(timeinfo));
    read(sockfd,&pid,1);

    printf("%d :: %d :: %d",hour,mins,sec);
    printf("The process id for the server is : %d",pid);
    close(sockfd);
    exit(0);
}
