#include "main.h"
#include "client.h"
#include "server.h"

int main(int argc, char** argv)
{
    struct Arguments myArgs;
    int opt;
    
    if (argc == 1) {
        display_help(argv);
        return(EXIT_SUCCESS);
    }
    
    memset(&myArgs, 0, sizeof(struct Arguments));
    memset(&myArgs.remoteHost, '\0', sizeof(char) * MAX_HOSTNAME_LENGTH);
    
    while ((opt = getopt(argc, argv, "hulp:vw")) != -1) {
        switch (opt) {
            case 'h': // Help
                display_help(argv);
                exit(EXIT_SUCCESS);
                break;
            case 'u': // UDP
                myArgs.udp = 1; 
                break;
            case 'l': // Listen (server mode)
                myArgs.listen = 1; 
                break;
            case 'p': // Server local port (server mode)
                myArgs.localPort = atoi(optarg);
                break;
            case 'v':
                fprintf(stdout, "netcatg version %s\n", VERSION);
                break;
            case 'w':
                // TODO: Client wait for reply after data is send
                break;
            default:  // Error, display help cmd
                fprintf(stderr, "%s -h for help\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    
    if (myArgs.listen == 1) {    // Server mode
        if (myArgs.localPort != 0) {
            server(myArgs);
        } else {
            fprintf(stderr, "Error, server mode: %s [-u] -l -p port\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        
    } else {                     // Client mode
        if (argc-optind >= 2 && atoi(argv[optind+1]) != 0) {
            strncpy(myArgs.remoteHost, argv[optind], MAX_HOSTNAME_LENGTH);
            myArgs.remotePort = atoi(argv[optind+1]);
            client(myArgs);
        } else {
            fprintf(stderr, "Error, client mode:  %s [-u] hostname port\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    return (EXIT_SUCCESS);
}


void display_help(char** argv)
{
    printf("%s v%s\n", argv[0]+2, VERSION);
    printf("Client mode:  %s [-u] hostname port\n", argv[0]);
    printf("Server mode:  %s [-u] -l -p port\n", argv[0]);
    printf("Options:\n");
    printf("        -h        Help\n");
    printf("        -u        UDP\n");                                    // TODO: Implement UDP server side
    printf("        -s        Silent -- Not implemented yet!\n");         // TODO: Silent Mode?
    printf("        -v        Show version\n");
    printf("        -w        Wait for server reply in client mode\n\n"); // TODO: Client wait for reply after data is send
}

