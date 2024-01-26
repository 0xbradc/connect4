/** @file main.c
 *
 * @brief Client in C
 *
 * @par
 * COPYRIGHT NOTICE: MIT License
 * See: https://en.wikibooks.org/wiki/C_Programming/Networking_in_UNIX
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct SocketInformation
{
   char *ip_address;
   unsigned int port_num;
};

int main()
{
   struct SocketInformation server_info;
   server_info.ip_address = "127.0.0.1";
   server_info.port_num = 4444;

   int sock;
   struct sockaddr_in server_addr;

   // Create socket
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (-1 == sock)
   {
      perror("Error creating socket");
      return 1;
   }

   // Set server address
   memset(&server_addr, 0, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(server_info.port_num);
   server_addr.sin_addr.s_addr = inet_addr(server_info.ip_address);

   // Connect to server
   if (0 > connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)))
   {
      perror("Connect failed");
      close(sock);
      return 1;
   }
   printf("Connected to the server on port %u from IP %s\n", server_info.port_num, server_info.ip_address);

   char input[1024];
   char buffer[1024];
   int n;

   while (1)
   {
      printf("Enter your move (column number): ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = 0; // Remove newline character

      // Send the move to the server
      send(sock, input, strlen(input), 0);

      // Read server's response
      n = recv(sock, buffer, sizeof(buffer) - 1, 0);
      if (n <= 0)
      {
         break;
      }
      buffer[n] = '\0'; // Null-terminate the string
      printf("Server says: %s\n", buffer);
   }

   close(sock);
   return 0;
}

/*** end of file ***/
