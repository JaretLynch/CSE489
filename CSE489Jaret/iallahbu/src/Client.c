#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <strings.h>

#include <string.h>

#include <arpa/inet.h>

#include <sys/types.h>

#include <netdb.h>

#include <unistd.h>

#include "../include/global.h"

#include "../include/logger.h"

#include "Commands.h"

int Portno;

void process_client_commands();

int LoggedIn=0;

int ClientFD;









int create_client_socket(int portno) {

	Portno=portno;

	int client_fd = socket(AF_INET, SOCK_STREAM, 0);

	

	if (client_fd < 0) {

		printf("\n Socket creation error \n");

		return -1;

	}

	else{

		process_client_commands();

		ClientFD=client_fd;

		return client_fd;

	}

	}







void close_connection(int client_fd) {



	close(client_fd);

}



void login_to_server(const char* server_ip, int server_port) {

	printf("\nLOGIN CALLED]\n");

	int sockfd;

	struct sockaddr_in serv_addr;



	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {

	

		perror("Socket Error");

		return;

	}



	serv_addr.sin_family = AF_INET;

	serv_addr.sin_port = htons(server_port);

	

	if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {

		printf("ERROR: Invalid IP address.\n");

		close(sockfd);

		return;

	}



	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {

		perror("Connect Error");

		close(sockfd);

		return;

	}

	else{

	printf("Logging in !/n");

	ClientFD=sockfd;

	LoggedIn=1;



        // Receive data from the server if needed.

        char MESSAGE[10];



	sprintf(MESSAGE, "%d", Portno);

        printf("Sent Data===%s\n",MESSAGE);

        int j=send(sockfd,MESSAGE,strlen(MESSAGE),0);

        if (j>0){

		printf("DATA SENT, %d bytes",j);

		}

		

		

	char *DataR = (char*) malloc(sizeof(char)*1024);

	int bytes_received = recv(sockfd, DataR, 1023,0);	

        

	while(bytes_received<=0){

		int bytes_received = recv(sockfd, DataR, 1023,0);	

		}

	DataR[bytes_received] = '\0';

        printf("Received from server: %s\n", DataR);

	// Send some message to server indicating login (depends on your protocol

	

process_client_commands();

	}





}

    void process_client_commands() {

    



    // The loop to keep client running and accept commands

    while(1) {

        printf("[PA1-Client@CSE489/589]$ \n");

	char *msg = (char*) malloc(sizeof(char)*256);







	fgets(msg, 256, stdin); // read from stdin

	msg[strlen(msg)-1]= '\0';

	printf("I got: %s(size:%lu chars)\n", msg, strlen(msg));

        if (strcmp(msg, "AUTHOR") == 0) {

            handle_author_command();

        } 

        else if (strcmp(msg, "IP") == 0) {

            handle_ip_command();

            free(msg);

        } 

        

        if (strcmp(msg,"PORT")==0){

			handle_port_command(Portno);

			free(msg);

		}

	if (strcmp(msg,"EXIT")==0){

			printf("TRYING TO CLOSE");

			close_connection(ClientFD);

			exit(-1);

		}

	if ((strcmp(msg,"REFRESH")==0) && (LoggedIn==1)){

        	printf("Sent Data===%s\n",msg);

        	int j=send(ClientFD,msg,strlen(msg),0);

        	char *DataR = (char*) malloc(sizeof(char)*1024);

		int bytes_received = recv(ClientFD, DataR, 1023,0);	

		

		while(bytes_received<=0){

			int bytes_received = recv(ClientFD, DataR, strlen(DataR),0);	

			}

		DataR[bytes_received] = '\0';

        	printf("Received from server: %s\n", DataR);

        	free(msg);

	

	}

	char *login = (char*) malloc(sizeof(char)*6);		

	strncpy(login,msg,5);

	login[5] = '\0' ;

	

	if ((strcmp(login,"LOGIN")==0) && (LoggedIn==0)){

		char *Cport;

		char *IP;

		Cport = (char*) malloc(30*sizeof(char));

		IP = (char*) malloc(30*sizeof(char));

		printf("LOGIN detected");

		int count=0;

		int iterator=0;

		int iterator2=0;

		for (int i=0; i<strlen(msg); i++){

		

			printf("%c\n",msg[i]);

			char Character[1];

			strncpy(Character,&msg[i],1);

			Character[1]='\0';

			

			if(count==1){

			

				IP[iterator2]=*Character;

				iterator2 ++;

			}

			

			

			if(count==2){

				

				Cport[iterator]=*Character;

				printf("Character is %c",*Character);

				iterator ++;

			}

			if (strcmp(Character," ")==0){

				count++;

				printf("DETECTED\n");

			}

	}

		IP[strlen(IP)-1]= '\0';

		int IPlen= strlen(IP);

		

		int Portlen= strlen(Cport);

		int PORTN= atoi(Cport);

		login_to_server(IP,PORTN);

		free(msg);

		}

			}

}
