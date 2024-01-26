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
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 500
#define PORTNUM 2300

/*!
 * @brief Set up main client
 *
 * @param[in] argc  Number of args
 * @param[in] argv  Array of args
 *
 * @return Success/Fail code
 */
int main()
{
   char buffer[MAXRCVLEN + 1]; // +1 so we can add null terminator
   int len;
   int server_socket;
   struct sockaddr_in dest;

   server_socket = socket(AF_INET, SOCK_STREAM, 0);

   memset(&dest, 0x0, sizeof(dest)); // Zero the struct
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = htonl(INADDR_ANY); // Set destination IP address
   dest.sin_port = htons(PORTNUM);           // Set destination port number

   connect(server_socket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
   len = recv(server_socket, buffer, MAXRCVLEN, 0);
   buffer[len] = '\0'; // We must null terminate the received data ourselves
   printf("Received %s (%d bytes).\n", buffer, len);

   const size_t BUF_SIZE = 256;
   while (1)
   {
      // Prompt for input
      char buffer[BUF_SIZE]; // Buffer to store the input, +1 for the null terminator
      printf("Enter a message to send to the server: ");
      if (fgets(buffer, sizeof(buffer) - 1, stdin)) 
      {
         buffer[strcspn(buffer, "\n")] = 0; // Remove newline character if present
         printf("You entered: %s\n", buffer);
      } 
      else 
      {
         printf("Error reading input.\n");
         continue; // Go through while-loop again
      }

      // Send inputted message
      int ret = send(server_socket, buffer, BUF_SIZE, 0);
      printf("Send return code: %d\n", ret);

      // Listen for response from server
      len = recv(server_socket, buffer, MAXRCVLEN, 0);
      buffer[len] = '\0'; // We must null terminate the received data ourselves
      printf("Received %s (%d bytes).\n", buffer, len);
   }
   

   close(server_socket);
   return EXIT_SUCCESS;
}

/*** end of file ***/
