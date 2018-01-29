#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"
#include "server.h"


struct Arguments {
        int udp;
        int listen;
        int port;
};
    

/* Display the help menu */
void display_help(char** argv);

#endif

