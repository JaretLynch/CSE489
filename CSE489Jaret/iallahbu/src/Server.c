#include "Server.h"

#include <arpa/inet.h>

#include <stdio.h>

#include <string.h>

#include <sys/socket.h>

#include <unistd.h>

#include <netinet/in.h>

#include <stdlib.h>

#include "../include/global.h"

#include "../include/logger.h"



#include "Commands.h"

#include "Server.h"

#include <netdb.h>

#define CMD_SIZE 100

#define BUFFER_SIZE 256

int server_socket;

struct sockaddr_in client_addr,server_addr;

fd_set master_list, watch_list;

int head_socket, selret, sock_index, fdaccept=0, caddr_len;

int PORT = 8080;  // default port, this can be set during server init

char buffer[1025];

/*int main(int argc, char *argv[]) {*/



typedef struct Client {

  char IPaddress[30];

  char Name[30];

  int ListeningPort;

  int FD;

} Clients;



Clients List[5];



char* ReturnMessage(const Clients LIST[]){

	char *ReturnM = malloc(1024);

	int id=1;

	for(int i=0; i<5; i++){

		int port_num= LIST[i].ListeningPort;

		if (port_num!=0){

			sprintf(ReturnM+strlen(ReturnM), "%-5d%-35s%-20s%-8d\n",id,LIST[i].Name,LIST[i].IPaddress, port_num);

			id+=1;

	}

}

	printf("RETURN MESSAGE IS %s",ReturnM);

	return	ReturnM;

}



int compareClients(const void *a, const void *b) {

    const Clients *clientA = (const Clients *)a;

    const Clients *clientB = (const Clients *)b;



    return clientA->ListeningPort - clientB->ListeningPort;

}







int AddClient(char ip[], char Name[], int LP, int FD) {

	Clients ClientToAdd;

	strcpy(ClientToAdd.IPaddress,ip);

	strcpy(ClientToAdd.Name,Name);

	ClientToAdd.ListeningPort=LP;

	ClientToAdd.FD=FD;

	for (int i=0; i<5; i++){

		int N=List[i].FD;

		if (N == 0){

			List[i]=ClientToAdd;

			return (0);

		}

		else{

	

}



}





return 0;

}





int Create_Server(int PortNO){



    	int port = PortNO;  // default port



    // Optionally handle command-line arguments to set port

/*    if (argc > 1) {*/

	if (1 > 1) {

	/*        port = atoi(argv[1]);*/

		port = 42;

		if (port <= 0) {

		    printf("Error: Invalid port number provided.\n");

		    return 1;

		}

	    }



	    // Initialize the server on the specified (or default) port

	    if (initialize_server(port) < 0) {

		printf("Error: Server initialization failed.\n");

		return 1;

	    }

	    else{

	    PORT=port;

	    // Start the main server loop

	    server_loop();

	    }

	    return 0;  // This line may not be reached if the server loop is infinite

	}





// Initialize the server

int initialize_server(int port) {



    PORT = port;



    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {

        perror("Socket creation failed");

        return -1;

    }



    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = INADDR_ANY;

    server_addr.sin_port = htons(PORT);



    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {

        printf("Bind failed\n");

        return -1;

    }



    if (listen(server_socket, 5) < 0) {  // 10 is the max number of waiting connections

        perror("Listen failed\n");

        return -1;

    }



    FD_ZERO(&master_list);

    FD_SET(server_socket, &master_list);

    FD_SET(0,&master_list);

    head_socket = server_socket;



    return 0;  // success

}



// Accept a new connection

int accept_new_connection() {



    int new_socket;

    socklen_t addr_len = sizeof(client_addr);



    new_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);

    if (new_socket < 0) {

        perror("Accept failed\n");

        return -1;

    }



    // Add to master_list

    FD_SET(new_socket, &master_list);

    if (new_socket > head_socket){

    	head_socket = new_socket;

    }

    

    

    return new_socket;

}



// Close and remove a connection

void remove_connection(int socket) {

    close(socket);

    FD_CLR(socket, &master_list);

    // You might also want to remove client information from any list you maintain.

}



// Main server loop, should be called after initializing the server

void server_loop() { 

	

	'\0';

	

	while (1) {

		memcpy(&watch_list, &master_list, sizeof(master_list));

		int STDIN= fileno(stdin);



		selret = select(head_socket + 1, &watch_list, NULL, NULL, NULL);

		

/*		char *msg = (char*) malloc(sizeof(char)*256);*/

/*	*/

/*		fgets(msg, 256, stdin); // read from stdin*/

/*	*/

/*		msg[strlen(msg)-1]= '\0';*/

		if(selret < 0)

			perror("select failed.\n");

		if(selret > 0){

		printf("Top Of While Loop\n");

			/* Loop through socket descriptors to check which ones are ready */

			for(sock_index=0; sock_index<=head_socket; sock_index+=1){

				

				if(FD_ISSET(sock_index, &watch_list)){

					

					/* Check if new command on STDIN */

					if (sock_index == STDIN){

						char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);

						

						memset(cmd, '\0', CMD_SIZE);

						if(fgets(cmd, CMD_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to cmd

							exit(-1);

						cmd[strlen(cmd)-1]='\0';

/*						printf("\nI got: %s\n. The length is %lu\n", cmd,strlen(cmd));*/

						

						

					

						if (strcmp(cmd,"Close")==0){

							remove_connection(head_socket);

							exit(-1);

						}

						

						

						if (strcmp(cmd,"AUTHOR")==0){

							printf("\n");

							handle_author_command();

						}

						if (strcmp(cmd,"IP")==0){

							handle_ip_command();

						}

						

						if (strcmp(cmd,"PORT")==0){

							handle_port_command(PORT);

						}

						else{

							printf("MESSAGE:%s\n",cmd);

							}



						free(cmd);

									}

						/* Check if new client is requesting connection */

						else if(sock_index == server_socket){

							caddr_len = sizeof(client_addr);

							fdaccept = accept(server_socket, (struct sockaddr *)&client_addr, &caddr_len);

							if(fdaccept < 0)

								perror("Accept failed.");

						

							printf("\nRemote Host connected!\n");                        

							char client_ip[INET_ADDRSTRLEN];

							char client_hostname[256];

							getnameinfo((struct sockaddr *)&client_addr, sizeof(client_addr), client_hostname, sizeof(client_hostname), NULL, 0, 0);

							inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

							

			

							

							printf("Client IP: %s\n", client_ip);

							printf("Client Hostname:%s\n",client_hostname);

							/* Add to watched socket list */

							FD_SET(fdaccept, &master_list);

							if(fdaccept > head_socket) {

							

								head_socket = fdaccept;

								}

							

							char *DataR = (char*) malloc(sizeof(char)*256);

							int bytes_received = recv(fdaccept, DataR, sizeof(DataR),0);

							if (bytes_received > 0) {

								printf("received %d bytes of data\n", bytes_received);

								DataR[bytes_received] = '\0';

								printf("Received from Client: %s\n", DataR);

							}



							

							AddClient(client_ip,client_hostname,atoi(DataR),fdaccept);

							qsort(List, 5, sizeof(Clients), compareClients);

							printf("\nSorted Clients by Port:\n");

							char *DataToSend= ReturnMessage(List);

							

							

						    

						    	

							

							send(fdaccept,DataToSend,strlen(DataToSend),0);

					}

					/* Read from existing clients */

					else{

						/* Initialize buffer to receieve response */

						char *buffer = (char*) malloc(sizeof(char)*256);

						memset(buffer, '\0', 256);

						

						if(recv(sock_index, buffer, 256, 0) <= 0){

							close(sock_index);

							printf("Remote Host terminated connection!\n");

							

							/* Remove from watched list */

							FD_CLR(sock_index, &master_list);

						}

						else {

							//Process incoming data from existing clients here ...

							

							printf("\nClient sent me: %s\n", buffer);

							printf("ECHOing it back to the remote host ... ");

							if(send(fdaccept, buffer, strlen(buffer), 0) == strlen(buffer))

								printf("Done!\n");

							fflush(stdout);

						}

						

						free(buffer);

					}

				}

			}

		}

	}

	

}
