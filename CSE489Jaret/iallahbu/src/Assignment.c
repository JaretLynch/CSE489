/**
 * @ubitname_assignment1
 * @author  Fullname <ubitname@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */
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

void main_loop(int sock, int port) {
    fd_set read_fds;
    char buffer[1024];

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(sock, &read_fds);

        select(sock + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            bzero(buffer, sizeof(buffer));
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            if (strcmp(buffer, "AUTHOR") == 0) {
                handle_author_command();
            } else if (strcmp(buffer, "IP") == 0) {
                handle_ip_command(sock);
            } else if (strcmp(buffer, "PORT") == 0) {
                handle_port_command(port);
            } else if (strcmp(buffer, "LIST") == 0) {
                handle_list_command();
            }
        } else if (FD_ISSET(sock, &read_fds)) {
            // TODO: Handle network events
        }
    }
}



/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */

int main(int argc, char **argv) {
    /*Init. Logger*/
    cse4589_init_log(argv[2]);

    /*Clear LOGFILE*/
    fclose(fopen(LOGFILE, "w"));

    /*Start Here*/
    if(argc != 3) {
        printf("Usage:%s [ip] [port]\n", argv[0]);
        exit(-1);
    }

    int port = atoi(argv[2]);
    // TODO: Create a socket and bind it to the port, then listen
    // int sock = ...;

    main_loop(sock, port);
    process_client_commands();
	
    return EXIT_SUCCESS;
}
