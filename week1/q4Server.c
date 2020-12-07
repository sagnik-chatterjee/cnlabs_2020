//Day time Server 
//Gets current time from the server , 


#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>



int main(){
	int server_sockfd,client_sockfd;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	//unnamed sockt for the server 
	server_sockfd= socket(AF_INET,SOCK_STREAM,0);
	//naming the soket 
	server_address.sin_family =AF_INET;
	server_address.sin_addr.s_addr =inet_addr("127.0.0.1");
	server_address.sin_port= 8080;
	server_len=sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

	//create a connection queueu and wait for clients 
	listen(server_sockfd,5);
	while(1){

		printf("[STATUS] Server Waiting ...\n");
		//accept a connection 
		client_len =sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
		
		//now read and write to client on client_sockfd 

		//char *ip_add =inet_ntoa(client_address.sin_addr);
		//int port= client_address.sin_port; 

		//get the localtime via asctime() 

		

		struct tm tm
        = *localtime(&(time_t){ time(NULL) }); 
		
		printf("The localtime defined now is %s:",asctime(&tm));
		//write(client_sockfd,&message,sizeof (message));
		close(client_sockfd);
		
	}	
}