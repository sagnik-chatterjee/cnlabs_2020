#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1000

int main()
{
	char **ans =(char**)malloc(100*sizeof(char *));//array for storing answer 
	
	int sockfd,n,len;
	struct sockaddr_in serveraddr,cliaddr;

	//clear server address and assigning new address to the server socket 
	bzero(&serveraddr,sizeof(serveraddr));
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	serveraddr.sin_family =AF_INET; 
	serveraddr.sin_addr.s_addr= htonl(INADDR_ANY);
	serveraddr.sin_port= htons(PORT);


	//bind the server address to socket descriptor 
	bind(sockfd,(
		struct sockaddr *)&serveraddr,sizeof(serveraddr));

	//recerive datagram 
	int k=0;
	while(1){
		char buffer[10];
		len=sizeof(cliaddr);
		n=recvfrom(sockfd,buffer,sizeof(buffer),0,
		(struct sockaddr *)&cliaddr,&len);
		buffer[n]='\0';

		printf("[STATUS] n : %d\n",n);
		if(strncmp("quit",buffer,4)==0){
			break;
		}
		ans[k]=(char *)malloc(sizeof(char)*n); 
		for(int j=0;j<n;j++){
			ans[k][j]=buffer[j];
		}
		k++;
		puts(buffer);
	}
	//Displaying the received matrix from the client 
	int i;
	printf("[STATUS] Displaying from the stored\n");
	for(int i=0;i<k;i++){
		printf("%s\t",ans[i]);
	}
	printf ("[STATUS] Exiting the server.\n");
	//close the descriptor 
	close(sockfd);

}