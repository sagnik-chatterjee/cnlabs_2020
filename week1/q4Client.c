#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 500 

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch;

/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 8080;
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("[STATUS] Some Error Occured..");
        exit(1);
    }

//now how do we get the server_file _desciptor 
    //and get read access to here 


/*  We can now read/write via sockfd.  */
    close(sockfd);
    exit(0);
}
