#include "client.h"


int client(int argc, char** argv)
{
    int sockfd;                    // Socket file descriptor
    int portno;                    // Remote server port
    struct hostent *server;        // Remote server host details
    struct sockaddr_in serv_addr;  // Server socket info

    // Validate server infos
    client_has_required_args(argc, argv);
    portno = atoi(argv[2]);
    server = gethostbyname(argv[1]);
    has_valid_hostname(server);
    
    // Create new TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        client_error("ERROR opening socket");
    
    // Set the internet socket address with server infos
    memset(&serv_addr, 0, sizeof(serv_addr)); // init struct to 0
    serv_addr.sin_family = AF_INET;
    memmove(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    serv_addr.sin_port = htons(portno);
    
    // Connect to remote server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        client_error("ERROR connecting");
    
    // Run client stuff
    do_client_processing(sockfd);
    
    close(sockfd);
    return (EXIT_SUCCESS);
}


void client_has_required_args(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
   }
}


void has_valid_hostname(struct hostent* server)
{
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }
}


void client_error(char *msg) // todo, same as server_error. Merge?
{
    perror(msg);
    exit(EXIT_FAILURE);
}


void do_client_processing(int sockfd)
{
    char buffer[BUFFER_SIZE]; // Send/Receive buffer
    int bytesCount;           // Socket read/write bytes counter

    while (1) {
        // Prompt user for input
        printf(COLOR_GREEN "[Client]: " COLOR_RESET);
        memset(&buffer, 0, sizeof(buffer));
        fgets(buffer, BUFFER_SIZE, stdin);

        // Handle program exit
        if (strcmp(buffer, EXIT_KEYWORD) == 0)
            break;

        // Send message to remote server
        bytesCount = write(sockfd, buffer, strlen(buffer));
        if (bytesCount < 0)
            client_error("ERROR writing to socket");
        printf(COLOR_GREEN "[Client]> %d bytes sent" COLOR_RESET "\n", bytesCount);
    }
}
