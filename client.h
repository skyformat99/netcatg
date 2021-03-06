#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "main.h" // struct Arguments

#define BUFFER_SIZE   255        // Send/Receive buffer size

#define COLOR_GREEN   "\x1b[32m" // Added some color for fun
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

/* Client main */
int client(struct Arguments myArgs);

/* Validate host/ip parameter */
void has_valid_hostname(struct hostent* server);

/* Core client processing */
void do_client_processing(int sockfd, struct Arguments myArgs);

/* Display detailed error code */
void client_error(char *msg);

#endif

