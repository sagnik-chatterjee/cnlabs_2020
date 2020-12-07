#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<ctype.h>
#define PORT 3004
#define sa struct sockaddr
int create_array(char* buff,int* n,int** arr){
    int num=0,temp=0,j=0;
    int* row;
    for(int i=0;i<strlen(buff)-1;i++){
        if(buff[i]==' '&&buff[i+1]!=' ')
            num++;
    }
    num++;
    if(*n&&num!=*n){
        return 0;
    }else{
        *n=num;
        if(num==0)
            return 0;
        row=malloc(num*sizeof(int));
        for(int i=0;i<strlen(buff);i++){
            if(buff[i]!=' ')
                temp=temp*10+buff[i]-48;
            else{
                row[j++]=temp;
                temp=0;
                while(buff[i]==' ') i++;
                i--;
            }
        }
        if(j<num){
            row[j]=temp;
        }
        *arr=row;
        return 1;
    }
}
int main(){
    int sockid=socket(AF_INET,SOCK_STREAM,0);
    int m=0,n=0,data_len,sockid_new;
    char buff[100];
    unsigned int len;
    struct sockaddr_in serv_addr,cli_addr;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(sockid,(sa*)&serv_addr,sizeof(serv_addr))<0){
        printf("[STATUS] Could not bind socket.\n");
        exit(0);
    }
    listen(sockid,5);
    len=sizeof(cli_addr);
    sockid_new=accept(sockid,(sa*)&cli_addr,&len);
    for(;;)
    {
        bzero(buff,sizeof(buff));
        read(sockid_new,buff,sizeof(buff));
        printf("[STATUS] Client with IP %s and port %d says : %s\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),buff);
        for(int i=0;i<strlen(buff);i++) buff[i]=toupper(buff[i]);
        write(sockid_new,buff,sizeof(buff));
        printf("[STATUS] String Returned to Client : %s\n",buff);
        if(strncmp(buff,"EXIT",4)==0) break;
    }
    printf("[STATUS] Server Shutting Down.\n");
    close(sockid);
    return 0;
}