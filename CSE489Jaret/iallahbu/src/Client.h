#ifndef CLIENT_H
#define CLIENT_H

int create_client_socket(int portno);
int connect_to_server(int client_fd, const char* server_ip, int server_port);
int send_message(int client_fd, const char* message);
int receive_message(int client_fd, char* buffer, int buffer_size);
void close_connection(int client_fd);
extern char local_ip[INET_ADDRSTRLEN];
void login_to_server(const char* server_ip, int server_port);

#endif // CLIENT_H
