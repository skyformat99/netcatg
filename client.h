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

#define EXIT_KEYWORD  "exit\n"   // Client termination keyword
#define BUFFER_SIZE   255        // Send/Receive buffer size

#define COLOR_GREEN   "\x1b[32m" // Added some color for fun
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

/* Client main */
int client(int argc, char** argv);

/* Validate command args */
void client_has_required_args(int argc, char** argv);

/* Validate host/ip parameter */
void has_valid_hostname(struct hostent* server);

/* Display detailed error code */
void client_error(char *msg);

/* Core client processing */
void do_client_processing(int sockfd);

#endif

