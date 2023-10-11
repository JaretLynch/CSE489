#ifndef SERVER_H
#define SERVER_H

int initialize_server(int port);
void server_loop();
void remove_connection(int socket);
int Create_Server(int PortNO);
#endif // SERVER_H
