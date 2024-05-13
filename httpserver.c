#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define PORT 4444

int main(){

    struct sockaddr_in server_address;
    int server_socketfd;

    const int opt = 1;

    if((server_socketfd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("failed to create the server socket");
        exit(1);
    }

    if(setsockopt(server_socketfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT ,&opt,sizeof(opt))<0){
        perror("failed to set options to the socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    //server_address.sin_addr.s_addr =  INADDR_ANY;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("server ip addr = %s\n",inet_ntoa(server_address.sin_addr));
    printf("server port = %d\n",ntohs(server_address.sin_port));
    printf("server socket fd = %d\n",server_socketfd);

    if(bind(server_socketfd,(struct sockaddr *)&server_address,sizeof(server_address))<0){
        perror("failed to bind the socket to the server address");
        exit(1);
    }

    if(listen(server_socketfd,5)<0){
        perror("failed to listen for incoming connections");
        exit(1);
    }

    printf("listening on port %d\n",PORT);

    struct sockaddr_in client_addresse;
    socklen_t client_addr_len = sizeof(client_addresse);
    int client_socketfd;
    

    char *buffer = (char*)calloc(1024,sizeof(char));
    char *response = "HTTP/1.1 200 OK\nContent-Type:text/html\n\nHello World;\n";

    while(1){

        if((client_socketfd=accept(server_socketfd,(struct sockaddr*)&client_addresse,&client_addr_len))<0){
            printf("Accept");
            continue;
        }
 
        read(client_socketfd,buffer,1024);
        printf("Received request: %s\n",buffer);

        //send(client_socketfd,response,strlen(response),0);
        write(client_socketfd,response,strlen(response));
        
        close(client_socketfd);
    }
    
    
    return 0;
}