/*
Day Time Client:
display server process id at the server side.
client sends request to time server to send current time 
*/

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

void cliFUnc(){

}



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

	//connect the clietn sopcket to server socket 
	if(connect(sockfd,(sa*)&servaddr,sizeof(servaddr))!=0){
		print("[STATUS] Connection with the server failed. \n");
		exit(0);
	}	
	else{
		printf("[STATUS] Connection with the server success !!\n");
	}
	//call the clifunc 
	clifunc(sockfd);
	//close the socket 
	close(sockfd);
}

