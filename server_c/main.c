/** @file main.c
 * 
 * @brief Server in C
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 * See: https://en.wikibooks.org/wiki/C_Programming/Networking_in_UNIX
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 2300

/*!
 * @brief Set up main server
 *
 * @param[in] argc  Number of args
 * @param[in] argv  Array of args
 *
 * @return Success/Fail code
 */
int main(int argc, char *argv[])
{
    struct sockaddr_in serv; // Socket info about our server
    struct sockaddr_in dest; // Socket info about the machine connecting to us
    int server_socket;       // Socket used to listen for incoming connections
    socklen_t socksize = sizeof(struct sockaddr_in);

    memset(&serv, 0, sizeof(serv));           // Zero the struct before filling the fields
    serv.sin_family = AF_INET;                // Set the type of connection to TCP/IP
    serv.sin_addr.s_addr = htonl(INADDR_ANY); // Set our address to any interface
    serv.sin_port = htons(PORTNUM);           // Set the server port number

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Bind serv information to server_socket
    bind(server_socket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

    // Start listening, allowing a queue of up to 1 pending connection
    listen(server_socket, 1);
    int client_socket = accept(server_socket, (struct sockaddr *)&dest, &socksize);

    const char* welcome_msg = "Hello, client. It's good to hear from you.";
    while (client_socket)
    {
        printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));
        send(client_socket, welcome_msg, strlen(welcome_msg), 0); // Send welcome message
        close(client_socket);
        client_socket = accept(server_socket, (struct sockaddr *)&dest, &socksize);
    }

    close(server_socket);
    return EXIT_SUCCESS;
}

/*** end of file ***/
