//Day time Server 
//Gets current time from the server , 
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int server_sockfd,client_sockfd;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	//unnamed sockt for the server 
	server_sockfd= socket(AF_INET,SOCK_STREAM,0);
	//naming the soket 
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family =AF_INET;
	server_address.sin_addr.s_addr =inet_addr("127.0.0.1");
	server_address.sin_port= 8080;
	server_len=sizeof(server_address);
	if(bind(server_sockfd,(struct sockaddr *)&server_address,server_len)==-1){
		printf("[STATUS] Could not bind socket.\n");
		exit(0);
	}

	//time things 
	time_t rawtime ;
	struct tm *timeinfo;
	char *reply; 
	int hour,mins,sec,pid; 
	
	//create a connection queueu and wait for clients 
	listen(server_sockfd,5);
	
	while(1){
	char ch;
	printf("[STATUS] Server Waiting ...\n");
		//accept a connection 
	client_len =sizeof(client_address);
	client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
		
	char *ip_add = inet_ntoa(client_address.sin_addr);
	int port= client_address.sin_port;
		
	printf("IP:%s , PORT:%d\n",ip_add,port);

	//time 
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	reply = asctime(timeinfo);

	hour = timeinfo-> tm_hour;
	mins =  timeinfo->tm_min; 
	sec  =   timeinfo->tm_sec;
	
	//local = localtime(&t);
	 pid=getpid() ;//for process id of the server 


	
	//writing the time and the process id back to the server 
	printf("[STATUS] Printing the localtime and the processid to the server\n");
	write(client_sockfd,&hour,1);
	write(client_sockfd,&mins,1);
	write(client_sockfd,&sec,1);
	write(client_sockfd,&pid,1);

	close(client_sockfd);
	}	
		
}
