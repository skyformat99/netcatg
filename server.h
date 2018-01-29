#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE  255        // Send/Receive buffer size
#define CLIENT_QUEUE 32         // Listen queue

#define COLOR_RED    "\x1b[31m" // Added some color for fun
#define COLOR_CYAN   "\x1b[36m"
#define COLOR_RESET  "\x1b[0m"

/* Server main */
int server(int argc, char** argv);

/* Validate command args */
void server_has_required_args(int argc, char** argv);

/* Display detailed error code */
void server_error(char *msg);

/* Code being executed for a connected client */
void do_server_processing(int newsockfd, struct sockaddr_in cli_addr);

/* SIGCHLD signal handling. Properly reap zombie at child termination */
void handle_sigchld(int sig);

#endif
