#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <strings.h>

#include <string.h>

#include <arpa/inet.h>

#include <sys/types.h>

#include <netdb.h>

#include <unistd.h>



#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <strings.h>

#include <string.h>

#include <arpa/inet.h>

#include <sys/types.h>

#include <netdb.h>

#include "Commands.h"

#include "Server.h"

#include "Client.h"



#define TRUE 1

#define MSG_SIZE 256

#define BUFFER_SIZE 256









void *get_in_addr(struct sockaddr *sa) {

    if (sa->sa_family == AF_INET) {

        return &(((struct sockaddr_in*)sa)->sin_addr);

    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);

}

int main(int argc, char **argv) {

	printf("Beginning of main\n");



	int sock;

	

	int rv;

	

	struct sockaddr_in googleAddr;

	

	char Message[BUFFER_SIZE];



	struct sockaddr_in localAddr;

	

	socklen_t addrSize;



	struct addrinfo hints, *servinfo;

	

	

/*	hints.ai_family = AF_INET;*/

/*	*/

/*	hints.ai_socktype = SOCK_DGRAM;*/



	char* server_ip = "8.8.8.8"; 

	

	char* server_port = "53";

	

	if (strcmp(argv[1],"s")==0){

		

		printf("Trying to start Server\n");

		int Port= atoi(argv[2]);

		Create_Server(Port);

	}

	

	else if(strcmp(argv[1],"c")==0){

	

		printf("Trying to start Client\n");

		int Port= atoi(argv[2]);

		create_client_socket(Port);

	}

	

	while(0){

	

	fgets(Message, BUFFER_SIZE, stdin); // read from stdin

	

  	int size = strlen(Message); //Total size of string

  	

	Message[size-1] = '\0';

	

	if (strcmp(Message,"IP")==0){

	

    	if ((rv = getaddrinfo(server_ip, server_port, &hints, &servinfo)) != 0) {

        		printf("getaddrinfo: %s\n", gai_strerror(rv));

       			exit(EXIT_FAILURE);

    }

    

    	if ((sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0) {

        	perror("socket() failed");

        	exit(EXIT_FAILURE);

    }



    	if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {

        	perror("connect() failed");

        	exit(EXIT_FAILURE);

    }

    

    	addrSize = sizeof(localAddr);

    	

    	if (getsockname(sock, (struct sockaddr *) &localAddr, &addrSize) < 0) {

    	

        	perror("getsockname() failed");

        	exit(EXIT_FAILURE);

        	

    		}

    		

	IP(inet_ntoa(localAddr.sin_addr));

	freeaddrinfo(servinfo);

	close(sock);

	

 	}

 	

 	if (strcmp(Message,"PORT")==0){

 	

/*		printf("[%s:SUCCESS]\n", Message);*/

/*		printf("Port:%u\n", ntohs(localAddr.sin_port));*/

/*		printf("[%s:END]\n", Message);*/

		unsigned int Port= ntohs(localAddr.sin_port);

		

		

 		}

 	}

   	return EXIT_SUCCESS;

    

}
