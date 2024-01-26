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
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_NUM 4444
#define BUFFER_SIZE 512

struct SocketInformation
{
   char *ip_address;
   unsigned int port_num;
};

void *handle_client(void *arg)
{
    int client_sock = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    ssize_t size;

    printf("New connection\n");

    while ((size = read(client_sock, buffer, BUFFER_SIZE)) > 0)
    {
        // Echo everything received
        write(client_sock, buffer, size);
        printf("Received: %.*s\n", (int)size, buffer);
    }

    if (size == 0)
    {
        printf("Client disconnected\n");
    }
    else
    {
        perror("Read error");
    }

    close(client_sock);
    return NULL;
}

int main()
{
    int server_sock, *client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_sock)
    {
        perror("Error creating socket");
        return 1;
    }

    // Set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUM);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind
    if (0 > bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Bind failed");
        close(server_sock);
        return 1;
    }

    // Listen
    if (0 > listen(server_sock, 5))
    {
        perror("Listen failed");
        close(server_sock);
        return 1;
    }

    printf("Server listening on port %d\n", PORT_NUM);

    // Accept connections
    while (1)
    {
        client_sock = malloc(sizeof(int));
        if (0 > (*client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len)))
        {
            perror("Accept failed");
            continue;
        }

        // Spawn a new thread for each connection
        if (0 != pthread_create(&thread, NULL, handle_client, client_sock))
        {
            perror("Thread creation failed");
            close(*client_sock);
            free(client_sock);
        }
        else
        {
            pthread_detach(thread); // Detach the thread
        }
    }

    // Never reached
    close(server_sock);
    return 0;
}

/*** end of file ***/
