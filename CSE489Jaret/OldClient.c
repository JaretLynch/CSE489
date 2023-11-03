
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



int ClientFD=-1;

fd_set watch_list;







int create_client_socket(int portno) {

	Portno=portno;

	int client_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (client_fd < 0) {

		cse4589_print_and_log("\n Socket creation error \n");

		return -1;

	}

	else{

		process_client_commands();



		ClientFD=client_fd;



		return client_fd;

	}

}



void Parse(char** Command,char** FirstArgPointer, char** SecondArgPointer, char* Actualmsg){

	int count=0;

	int iterator1=0;

	int iterator2=0;

	int iterator3=0;

	

	int j=strlen(Actualmsg);

	printf("Length of Command is %d\n",j);

	for (int i=0; i<strlen(Actualmsg); i++){

		char Character[1];

		strncpy(Character,&Actualmsg[i],1);

		Character[1]='\0';

		if(count==1){

			(*FirstArgPointer)[iterator2]=*Character;

			iterator2 ++;

		}

		if (count>1){

			(*SecondArgPointer)[iterator3]=*Character;

			iterator3++;

		}

		if (strcmp(Character," ")==0){

			count++;



		}

		if (count==0){

			(*Command)[iterator1]=*Character;

			iterator1++;		

		}

		}

}

void ParseServerMessage(char** ServerCommand,char* ServerMessage){

	int count=0;

	int iterator1=0;

	

	int j=strlen(ServerMessage);

	for (int i=0; i<strlen(ServerMessage); i++){

		char Character[1];

		strncpy(Character,&ServerMessage[i],1);

		Character[1]='\0';

		if (strcmp(Character," ")==0){

			count++;

		}

		if (count==0){

			(*ServerCommand)[iterator1]=*Character;

			iterator1++;		

		}

		}

}



void close_connection(int client_fd) {

	close(client_fd);

}



void login_to_server(const char* server_ip, int server_port) {



	struct sockaddr_in serv_addr;



	if ((ClientFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) {



		cse4589_print_and_log("[LOGIN:ERROR]\n");

		cse4589_print_and_log("[LOGIN:END]\n");

		ClientFD=-1;

		return;

	}

	serv_addr.sin_family = AF_INET;



	serv_addr.sin_port = htons(server_port);



	if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {



		cse4589_print_and_log("[LOGIN:ERROR]\n");

		cse4589_print_and_log("[LOGIN:END]\n");

		ClientFD=-1;

		close(ClientFD);

		return;

	}

	if (connect(ClientFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {



		cse4589_print_and_log("[LOGIN:ERROR]\n");

		cse4589_print_and_log("[LOGIN:END]\n");

		ClientFD=-1;

		close(ClientFD);

		return;

	}

	else{

		cse4589_print_and_log("[LOGIN:SUCCESS]\n");

		cse4589_print_and_log("[LOGIN:END]\n");

		LoggedIn=1;



		char MESSAGE[10];



		sprintf(MESSAGE, "%d", Portno);



		int j=send(ClientFD,MESSAGE,strlen(MESSAGE),0);	



/*		char *DataR = (char*) malloc(sizeof(char)*1024);*/



/*		int bytes_received = recv(ClientFD, DataR, 1023,0);	*/



/*		while(bytes_received<=0){*/



/*			int bytes_received = recv(ClientFD, DataR, 1023,0);	*/



/*		}*/

/*		DataR[bytes_received] = '\0';*/



/*		cse4589_print_and_log("%s", DataR);*/

/*		FD_SET(ClientFD, &watch_list);*/

		process_client_commands();

	}

}



void process_client_commands() {

	// The loop to keep client running and accept commands



	while(1) {

		FD_ZERO(&watch_list);

		FD_SET(0,&watch_list);

	

		if(ClientFD!=-1){

			FD_SET(ClientFD,&watch_list);

		}

		printf("TOP OF LOOP\n");

		fflush(stdout);

		int selret = select(10, &watch_list, NULL, NULL, NULL);

		if(selret < 0){

       

			perror("select failed.\n");



		}

		if(selret >= 0){

			printf("SELRET IS %d\n",selret);

			for (int i=0; i<10; i++){

				if (FD_ISSET(i, &watch_list)) {

            			printf("File descriptor %d is set in the set.\n", i);

            			fflush(stdout);

        			}

    			}

			for(int sock_index=0; sock_index<=5; sock_index+=1){



				if(FD_ISSET(sock_index, &watch_list)){



					if (sock_index == 0){

						char *Input = (char*) malloc(sizeof(char)*256);



						char *login = (char*) malloc(sizeof(char)*6);		

						

						char *Command= (char*) malloc(sizeof(char)*256);

						

						char *Arg1 = (char*) malloc(sizeof(char)*256);

						

						char *Arg2 = (char*) malloc(sizeof(char)*256);

						

						fgets(Input, 256, stdin);

						

						Parse(&Command,&Arg1,&Arg2,Input);

						Input[strlen(Input)-1]= '\0';



						strncpy(login,Input,5);

						



						login[5] = '\0' ;



						if (strcmp(Input, "AUTHOR") == 0) {



							handle_author_command();



						} 



						else if (strcmp(Input, "IP") == 0) {



							handle_ip_command();



						} 



						else if (strcmp(Input,"PORT")==0){



							handle_port_command(Portno);



						}



						else if (strcmp(Input,"EXIT")==0){



							cse4589_print_and_log("[EXIT:SUCCESS]\n");



							cse4589_print_and_log("[EXIT:END]\n");



							close_connection(ClientFD);



							exit(-1);



						}

						if (LoggedIn==0){

							if ((strcmp(login,"LOGIN")==0)){

							

	/*							char *Client_Port = (char*) malloc(30*sizeof(char));*/



	/*							char *Client_IP = (char*) malloc(30*sizeof(char));*/



	/*							int count=0;*/



	/*							int iterator=0;*/



	/*							int iterator2=0;*/



	/*							for (int i=0; i<strlen(msg); i++){*/



	/*								char Character[1];*/



	/*								strncpy(Character,&msg[i],1);*/



	/*								Character[1]='\0';*/



	/*								if(count==1){*/



	/*									Client_IP[iterator2]=*Character;*/



	/*									iterator2 ++;*/



	/*								}*/



	/*								if(count==2){*/



	/*									Client_Port[iterator]=*Character;*/



	/*									iterator ++;*/



	/*								}*/



	/*								if (strcmp(Character," ")==0){*/



	/*									count++;*/



	/*								}*/

	/*							}*/

								Arg1[strlen(Arg1)-1]= '\0';



								int IPlen= strlen(Arg1);



								int PORTN= atoi(Arg2);



								login_to_server(Arg1,PORTN);



								free(Input);



							}

						if (LoggedIn==1){

					

						if (strcmp("REFRESH",Input)==0){

							int j=send(ClientFD,Input,strlen(Input),0);

	/*						char *DataR = (char*) malloc(sizeof(char)*1024);*/



	/*						*/

	/*						DataR[bytes_received] = '\0';*/



	/*						cse4589_print_and_log("[REFRESH:SUCCESS]\n");*/



	/*						cse4589_print_and_log("%s", DataR);*/



	/*						cse4589_print_and_log("[REFRESH:END]\n");*/



							free(Input);

						}

						else if (strcmp(Input,"LIST")==0){

							int j=send(ClientFD,Input,strlen(Input),0);



	/*						char *DataR = (char*) malloc(sizeof(char)*1024);*/



	/*						int bytes_received = recv(ClientFD, DataR, 1023,0);	*/



	/*						while(bytes_received<=0){*/



	/*							int bytes_received = recv(ClientFD, DataR, strlen(DataR),0);	*/



	/*						}*/



	/*						DataR[bytes_received] = '\0';*/



	/*						cse4589_print_and_log("[LIST:SUCCESS]\n");*/



	/*						cse4589_print_and_log("%s", DataR);*/



	/*						cse4589_print_and_log("[LIST:END]\n");*/



							free(Input);



						}

						

/*						else if ((strcmp(login,"LOGIN")==0)){*/

/*						*/

/*							char *Client_Port = (char*) malloc(30*sizeof(char));*/



/*							char *Client_IP = (char*) malloc(30*sizeof(char));*/



/*							int count=0;*/



/*							int iterator=0;*/



/*							int iterator2=0;*/



/*							for (int i=0; i<strlen(msg); i++){*/



/*								char Character[1];*/



/*								strncpy(Character,&msg[i],1);*/



/*								Character[1]='\0';*/



/*								if(count==1){*/



/*									Client_IP[iterator2]=*Character;*/



/*									iterator2 ++;*/



/*								}*/



/*								if(count==2){*/



/*									Client_Port[iterator]=*Character;*/



/*									iterator ++;*/



/*								}*/



/*								if (strcmp(Character," ")==0){*/



/*									count++;*/



/*								}*/

/*							}*/

/*							Client_IP[strlen(Client_IP)-1]= '\0';*/



/*							int IPlen= strlen(Client_IP);*/



/*							int Portlen= strlen(Client_Port);*/



/*							int PORTN= atoi(Client_Port);*/



/*							login_to_server(Client_IP,PORTN);*/



/*							free(msg);*/



/*						}*/



					}

				}

				if (strcmp(Command,"SEND")==0){

						int LengthOfMessageSent=send(ClientFD,Input,strlen(Input),0);

/*						if (LengthOfMessageReceived==1){*/

/*							cse4589_print_and_log("[%s:SUCCESS]\n","SEND");*/

/*							cse4589_print_and_log("[%s:END]\n","SEND");*/

/*						}*/

/*						else if (LengthOfMessageReceived==2){*/

/*							cse4589_print_and_log("[%s:ERROR]\n","SEND");*/

/*							cse4589_print_and_log("[%s:END]\n","SEND");*/

/*						}*/

					}

				else{



					cse4589_print_and_log("[%s:ERROR]\n",Input);

					cse4589_print_and_log("[%s:END]\n",Input);

					fflush(stdout);

					}

				}

				}

				//END OF READING FROM STDIN

				if ((LoggedIn==1)&&(sock_index!=0)){

					char *DataReceived= (char*) malloc(256*sizeof(char));

					char *ClientCommand= (char*) malloc(256*sizeof(char));

					char *Arg1= (char*) malloc(256*sizeof(char));

					char *Arg2 = (char*) malloc(256*sizeof(char));

					char *ServerCommand=(char*) malloc(256*sizeof(char));

/*					Parse(&ClientCommand,&Arg1,&Arg2,Input);*/

					cse4589_print_and_log("ClientCommand is %s\n",ClientCommand);

					cse4589_print_and_log("Arg1 is %s\n",Arg1);

					cse4589_print_and_log("Arg2 is %s\n",Arg2);

					

					printf("CLIENT COMMAND IS *%s*\n",ClientCommand);

					if (strcmp(ClientCommand,"LOGOUT")==0){

						send(ClientFD,"LOGOUT",strlen("LOGOUT"),0);

						close_connection(ClientFD);

						FD_CLR(ClientFD,&watch_list);

						ClientFD=-1;

						LoggedIn=0;

						printf("strcmp LOGOUT ACHIEVED");

					}



					if (strcmp(ServerCommand,"RELAYED")==0){

						cse4589_print_and_log("RELAYED\n");

						cse4589_print_and_log("%s\n",DataReceived);

					}

					int LengthOfMessageReceived= recv(ClientFD, DataReceived, 1023,0);

/*					if (strcmp(ClientCommand,"SEND")==0){*/

/*						int LengthOfMessageSent=send(ClientFD,Input,strlen(Input),0);*/

/*						if (LengthOfMessageReceived==1){*/

/*							cse4589_print_and_log("[%s:SUCCESS]\n","SEND");*/

/*							cse4589_print_and_log("[%s:END]\n","SEND");*/

/*						}*/

/*						else if (LengthOfMessageReceived==2){*/

/*							cse4589_print_and_log("[%s:ERROR]\n","SEND");*/

/*							cse4589_print_and_log("[%s:END]\n","SEND");*/

/*						}*/

/*					}*/

			}

			//socket index is server//

/*			else if (sock_index==ClientFD){*/

/*				char *DataReceived= (char*) malloc(1023*sizeof(char));*/

/*				char *ClientCommand= (char*) malloc(256*sizeof(char));*/

/*				char *Arg1= (char*) malloc(256*sizeof(char));*/

/*				char *Arg2 = (char*) malloc(256*sizeof(char));*/

/*				char *ServerCommand=(char*) malloc(256*sizeof(char));	*/

/*			Parse(&ClientCommand,&Arg1,&Arg2,msg);*/

/*				int LengthOfMessageReceived= recv(ClientFD, DataReceived, 1023,0);*/

/*				ParseServerMessage(&ServerCommand,DataReceived);*/

/*				if(strcmp(ServerCommand,"RELAYED")==0){*/

/*					cse4589_print_and_log("[%s:SUCCESS]\n","RECEIVED");*/

/*					cse4589_print_and_log("%s",DataReceived);*/

/*					cse4589_print_and_log("[%s:END]\n","RECEIVED");*/

/*				}*/

/*				fflush(stdout);*/

/*		*/

/*			}*/

		}

		}

	}



}
