
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include "Client.h"
#include "Commands.h"
#include "Server.h"
#include "../include/global.h"
#include "../include/logger.h"
// Forward declaration of shell command handlers
void handle_author_command();
void handle_ip_command();
void handle_port_command();
void handle_list_command();
// Forward declaration of shell command handlers
void login_to_server(const char* server_ip, int server_port);
char local_ip[INET_ADDRSTRLEN];
int listening_port;



//...

/*void login_to_server(const char* server_ip, int server_port) {*/
/*    const char *command_str = "LOGIN";*/

/*    // TODO: Logic to connect to server, send login request, and handle server's response*/
/*    */
/*    cse4589_print_and_log("[%s:SUCCESS]\n", command_str);*/
/*    cse4589_print_and_log("Logged in to server %s at port %d\n", server_ip, server_port);*/
/*    cse4589_print_and_log("[%s:END]\n", command_str);*/
/*}*/


void handle_author_command() {
    const char *command_str = "AUTHOR";
    const char *ubit_name = "Jaretlyn";  // TODO: Replace with your UBIT name
/*    cse4589_print_and_log("[%s:SUCCESS]\n", command_str);*/
/*    cse4589_print_and_log("I, %s, have read and understood the course academic integrity policy.\n", ubit_name);*/
/*    cse4589_print_and_log("[%s:END]\n", command_str);*/
	printf("[%s:SUCCESS]\n", command_str);
	printf("I, %s, have read and understood the course academic integrity policy.\n", ubit_name);
	printf("[%s:END]\n", command_str);
}


// Global variable for local IP address


void handle_ip_command(const char *Address) {


    struct sockaddr_in serv_addr, local_addr;
    socklen_t addr_len = sizeof(local_addr);


    int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_port = htons(53);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("8.8.8.8");

    if (connect(socket_desc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        return;
    }



    if (getsockname(socket_desc, (struct sockaddr *)&local_addr, &addr_len) < 0) {
        perror("getsockname failed");
        return;
    }


    char ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &local_addr.sin_addr, ip, INET_ADDRSTRLEN);
    close(socket_desc);
    printf("%s", ip);
    printf("[%s:SUCCESS]\n", "IP");
    printf("IP:%s\n", Address);
    printf("[%s:END]\n", "IP");
	struct sockaddr *addr, *dummy;
	
	printf("1\n");
	
	socklen_t *dummy1;
	
	printf("2\n");
	
	
	struct sockaddr_in *serv_addr;
	
	printf("3\n");
	
	int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
	printf("4\n");
		
    	serv_addr->sin_port = htons(53);
    	
    	serv_addr->sin_family = AF_INET;
    	
	printf("6\n");
	
    	serv_addr->sin_addr.s_addr = inet_addr("8.8.8.8");
    		
	printf("7\n");
	
    	int socket = connect(socket_desc, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    		
	printf("8\n");
	
    	getsockname(socket, dummy, dummy1);
    		
	printf("9\n");
	
    	
    	char ip[20];
    		
	printf("10\n");
	
    	struct sockaddr_in *s = (struct sockaddr_in *)&dummy;
    		
	printf("11\n");
	
        inet_ntop(AF_INET, &s->sin_addr, ip, *dummy1);
        	
	printf("12\n");
	
        close(socket);
        	
	printf("13\n");
	
    	printf("%s",ip);
    	
    	
    	const char *command_str = "IP";
    
    if (strlen(Address) == 0) { // Check if the IP address has been set
/*        cse4589_print_and_log("[%s:ERROR]\n", command_str);*/
/*        cse4589_print_and_log("IP address not set.\n");*/
/*        cse4589_print_and_log("[%s:END]\n", command_str);*/
	printf("[%s:ERROR]\n", command_str);
        printf("IP address not set.\n");
        printf("[%s:END]\n", command_str);
        return;
    }
/*	cse4589_print_and_log("[%s:SUCCESS]\n", command_str);*/
/*	cse4589_print_and_log("IP:%s\n", local_ip);*/
/*	cse4589_print_and_log("[%s:END]\n", command_str);*/
	printf("[%s:SUCCESS]\n", command_str);
	printf("IP:%s\n", Address);
	printf("[%s:END]\n", command_str);
}


void handle_port_command(int listening_port) {
    const char *command_str = "PORT";
/*    cse4589_print_and_log("[%s:SUCCESS]\n", command_str);*/
/*    cse4589_print_and_log("PORT:%d\n", listening_port);*/
/*    cse4589_print_and_log("[%s:END]\n", command_str);*/
	printf("[%s:SUCCESS]\n", command_str);
	printf("PORT:%d\n", listening_port);
	printf("[%s:END]\n", command_str);
}

// Stub function for handling the LIST command
void handle_list_command() {
    const char *command_str = "LIST";
    // TODO: Retrieve the list of connected clients and print them

/*    cse4589_print_and_log("[%s:SUCCESS]\n", command_str);*/
/*    // For now, we'll print a dummy client. This should be replaced by actual data later.*/
/*    cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", 1, "dummy.cse.buffalo.edu", "128.205.36.46", 4545);*/
/*    cse4589_print_and_log("[%s:END]\n", command_str);*/
}
