#include "main.h"

int main(int argc, char** argv)
{
    struct Arguments myArgs;
    memset(&myArgs, 0, sizeof(struct Arguments));
    int opt;
    
    while ((opt = getopt(argc, argv, "hulp:")) != -1) {
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
            case 'p': // Port
                myArgs.port = atoi(optarg);
                if (myArgs.port == 0) {
                    fprintf(stderr, "Error, specified port is not valid.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:  // Error, display help cmd
                fprintf(stderr, "%s -h for help\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    
    if (myArgs.listen == 1) {
        // server mode
        //server(argc, argv);
    } else {
        // client mode
        client(argc-optind, argv+optind); // Send argc and argv, without the options part
    }

    return (EXIT_SUCCESS);
}


void display_help(char** argv)
{
    printf("Client mode:  %s [-u] hostname port\n", argv[0]);
    printf("Server mode:  %s [-u] -l -p port\n", argv[0]);
    printf("Options:\n");
    printf("        -h        Help\n");
    printf("        -u        UDP -- Not implemented yet!\n");       // TODO: Implement UDP
    printf("        -s        Silent -- Not implemented yet!\n");    // TODO: Silent Mode?
    printf("        -v        Verbose -- Not implemented yet!\n\n"); // TODO: Verbose Mode?
}

