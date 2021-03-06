#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_HOSTNAME_LENGTH 255
#define VERSION "0.1"

struct Arguments {
        int udp;
        int listen;
        int localPort;
        int waitReply;
        int remotePort;
        char remoteHost[MAX_HOSTNAME_LENGTH];
};
    

/* Display the help menu */
void display_help(char** argv);

#endif

