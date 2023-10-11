#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int sockfd, newsockfd, port, n;
    struct sockaddr_in server_address, client_addr;
    socklen_t clilen;
    
    int opt = 1;
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";
  
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }
    
    bzero((char *) &server_address, sizeof(server_address));
    port= atoi(argv[1]);
    
    server_address.sin_family= AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port=htons(port);
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address))<0){
    	printf("bind failed");
}	
	else{
	printf("Bind successful");
	}
	while(1){
	listen(sockfd,4);
	clilen=sizeof(client_addr);
	bzero(buffer,sizeof(buffer));
	n=read(newsockfd,buffer,sizeof(buffer));
	if (n<0){
	
	printf("error when reading");
	}
	printf("Client : %s\n", buffer);
	bzero(buffer,sizeof(buffer));
	fgets(buffer,sizeof(buffer),stdin);
	n=write(newsockfd, buffer, strlen(buffer));
	int i=strncmp(buffer,"Bye",3);
	if (i==0){
	break;}
	}
    close(newsockfd);
    close(sockfd);
    return 0;
    }
    
    
    
    
    
    
    
    
    
    
    
    
