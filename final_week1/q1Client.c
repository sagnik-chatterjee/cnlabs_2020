#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 8080
#define MAXLINE 1000

int main()
{
	int sockfd,n,len;
	struct sockaddr_in serveraddr,cliaddr;

	//clear serveraddr
	bzero(&serveraddr,sizeof(serveraddr));
	sockfd= socket(AF_INET,SOCK_DGRAM,0);
	serveraddr.sin_addr.s_addr= htonl(INADDR_ANY);
	serveraddr.sin_port= htons(PORT);
	serveraddr.sin_family=AF_INET ;

	
	//main logic loop
	while(1){
		char buffer[10];
		printf("[STATUS] Enter a row of a matrix:\t");
		scanf("%s",buffer);
		sendto(sockfd,buffer,strlen(buffer),0,(
			struct sockaddr *
		)&serveraddr,sizeof(serveraddr));

		if(strncmp("quit",buffer,4)==0){
			break;
		}
	}

	printf("[STATUS] Exiting the program.");
	
	//close the descriptor 
	close(sockfd);
	


}
