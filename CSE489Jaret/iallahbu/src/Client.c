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

	printf("LOG THE FUCK IN\n ");

	LoggedIn=1;



        // Receive data from the server if needed.

        

        char *DataToSend;

	DataToSend = (char*) malloc(255*sizeof(char));

        strcpy(DataToSend,"MESSAGESEND");

        if (send(sockfd,DataToSend,sizeof(DataToSend),0)>0);

		printf("DATA SENT");

        char *received_data;

        received_data = (char*) malloc(255*sizeof(char));

        int bytes_received = recv(sockfd, received_data, sizeof(received_data),0);

        if (bytes_received > 0) {

            received_data[bytes_received] = '\0';

            printf("Received from server: %s\n", received_data);

	}



	// Send some message to server indicating login (depends on your protocol

	else {

		(printf("BYTES RECEIVED <=0"));

		}

	// Receive list of logged-in clients and buffered messages

	// Logic to handle received data here

	close(sockfd);

	printf("SOCKET CLOSED");

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

        } 

        

        if (strcmp(msg,"PORT")==0){

			handle_port_command(Portno);

		}

	if (strcmp(msg,"CLOSE")==0){

			printf("TRYING TO CLOSE");

			close_connection(ClientFD);

			exit(-1);

		}

	char *login = (char*) malloc(sizeof(char)*6);		

	strncpy(login,msg,5);

	login[5] = '\0' ;

	

	if (strcmp(login,"LOGIN")==0){

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

		Portlen= strlen(Cport);

		printf("Length is %d",IPlen);

		printf("\nFINAL IP IS %s",IP);

		printf("\nFINAL LENGTH IS %d\n",IPlen);

		printf("First character is %c\n",IP[0]);

		printf("Last character is %c\n",IP[IPlen-1]);

		

		printf("Length is %d",Portlen);

		printf("\nFINAL Port IS %s",Cport);

		printf("\nFINAL LENGTH IS %d\n",Portlen);

		printf("First character is %c\n",Cport[0]);

		printf("Last character is %c\n",Cport[Portlen-1]);

		

		int PORTN= atoi(Cport);

		login_to_server(IP,PORTN);

		}

			}

/*	else if (strcmp(msg, "LOGIN") == 0) {*/

/*            char server_ip[100];*/

/*            int server_port;*/

/*          sscanf(buffer, "LOGIN %s %d", server_ip, &server_port);*/

/*            login_to_server(server_ip, server_port);*/

/*        }*/

        // ... and so on for other commands

    }





/*int main(int argc, char *argv[]) {*/

/*    // Initialization or setup code, if any...*/

/*    char host[256];*/

/*    struct hostent *host_entry;*/

/*    gethostname(host, sizeof(host));*/

/*    host_entry = gethostbyname(host);*/

/*    strcpy(local_ip, inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])));*/





/*    process_client_commands(); // This will start your command loop*/



/*    return 0; // Return successful exit status*/

/*}*/
