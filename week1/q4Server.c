//Day time Server 
//Gets current time from the server , 
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netint/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define sa struct sockaddr

#define PORT 8080
#define MAX 80 




int main(){
	int sockfd,connfd;
	struct sockaddr_in ,servaddr,cli;

	//sockert create and verify 
	sockfd=  socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("[STATUS] Socket creation failed ...\n");
		exit(0);
	}
	else{
		printf("[STATUS] Socket successfully created ...\n");
	}
	
	bzero(&servaddr,sizeof(servaddr));

	//asign ip and port 
	servaddr.sin_family= AF_INET;
	servaddr.sin_addr.sin_addr=inet_addr("127.0.0.1");
	servaddr.sin_port= htons(PORT);

	//bind the newly created socket to given ip and verification 
	if((bind(sockfd,(sa*)&servaddr,sizeof(servaddr)))!=0){
		printf("[STATUS] Socket bind failed ... \n");
		exit(0);
		
	}


}
