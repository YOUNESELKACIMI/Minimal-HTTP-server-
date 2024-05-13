#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 4444

int main(){

    int client_socketfd;
    struct sockaddr_in server_address;
    
    if((client_socketfd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("failed to create the client's socket");
        exit(1);
    }

    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(PORT);
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");


    if(connect(client_socketfd,(struct sockaddr *)&server_address,sizeof(server_address))<0){
        perror("failed to connect to the server's socket");
        exit(1);
    }


    char *buffer = (char *)calloc(1024,sizeof(char));
    char *hello = "Hello from Client";
    
    write(client_socketfd,hello,strlen(hello));
    //send(client_socketfd,hello,strlen(hello),0);
    printf("message '%s' is sent to the server\n",hello);

    read(client_socketfd,buffer,1024);
 

    printf("message received from the server : %s\n",buffer);

    close(client_socketfd);
    free(buffer);
    return 0;
}