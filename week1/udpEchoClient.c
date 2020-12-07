#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080 


int main(){
	char buffer[100];
	char message[100];
	printf("Enter the message... \n");
	gets(message);

	int sockfd,n,len;
	struct sockaddr_in servaddr,cliaddr;

	//clear servaddr
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET; //ipv4 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);

	//datagram socket creation 
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	sendto(sockfd,message,MAXLINE,0,
		(struct sockaddr*)&servaddr,sizeof(servaddr));

	len=sizeof(servaddr);

	//wait for response 
	n=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);

	buffer[n]='\0';

	printf("[STATUS] Message from server is %s\n",buffer);
	getchar();

	//close descriptor 
	close(sockfd);


}