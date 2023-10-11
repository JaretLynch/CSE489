// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

int IP(); 

void handle_author_command();
void handle_ip_command();
void handle_port_command();
void login_to_server(const char* server_ip, int server_port);
extern char local_ip[INET_ADDRSTRLEN];

// ... any other command handler declarations

#endif // COMMANDS_H
