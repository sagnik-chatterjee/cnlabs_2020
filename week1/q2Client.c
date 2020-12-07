/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 8080

int main(){
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = PORT;
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("[STATUS] Error Reported.");
        exit(1);
    }

/*  We can now read/write via sockfd.  */
    printf("[STATUS] Please Type String to send:");
    //scanf("%c", &ch); 
    char input_str[13];//13 char string which is sent to server 
    gets(input_str);
    write(sockfd, &input_str, 13);
    read(sockfd, &ch, 13);
    printf("[STATUS] Char from Server Received = %c\n", ch);
    close(sockfd);
    exit(0);
}
