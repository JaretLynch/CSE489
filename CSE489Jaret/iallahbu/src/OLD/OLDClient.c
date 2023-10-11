#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int sockfd, newsockfd, port, n;
    struct sockaddr_in server_address;
    struct hostent *server;
    socklen_t clilen;
    
    char buffer[1024];
    if (argc <3){
    printf("error, not enough arguments");
    exit(0);
    }
    
   

  
    // Creating socket file descriptor
   
    port= atoi(argv[2]);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }
    if (server==NULL){
    printf("Error, server not started");
    	
    server= gethostbyname(argv[1]);
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family= AF_INET;
    
    bcopy((char *) server-> h_addr, (char *) server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port= htons(port);
    
    
    
    
    
    server_address.sin_port=htons(port);
    
    if (connect(sockfd, (struct sockaddr *) &server_address, sizeof(server_address))<0){
    	printf("connection failed failed");
}	
	else{
	printf("connection successful");
	}
	while(1){
	bzero(buffer, 1024);
	fgets(buffer,sizeof(buffer),stdin);
	n=read(newsockfd, buffer, strlen(buffer));
	
	
	int i=strncmp(buffer,"Bye",3);
	if (i==0){
	break;}
	}
    close(newsockfd);
    close(sockfd);
    return 0;
    }
    }
    
    
