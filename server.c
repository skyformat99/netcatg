#include "server.h"

int server(struct Arguments myArgs)
{
    int ssockfd;                                    // Server Listening socket
    int csockfd;                                    // Client Connection socket
    struct sockaddr_in serv_addr, cli_addr;         // Server & Client socket info
    socklen_t socklen = sizeof(struct sockaddr_in); // Socket info size
    struct sigaction sa;                            // SIGCHLD management, for zombie
    pid_t pid;                                      // Child pid
    
    
    // Create new TCP socket
    ssockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (ssockfd < 0)
        server_error("ERROR opening socket");
    
    // Set the internet socket address with server infos
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(myArgs.localPort);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    // Bind server socket to port
    if (bind(ssockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        server_error("ERROR on binding");
    printf(COLOR_CYAN "Server now listening on port %d." COLOR_RESET "\n", ntohs(serv_addr.sin_port));
    listen(ssockfd, CLIENT_QUEUE);
    
    // Handle SIGCHLD signal to reap zombie when a child terminate
    sa.sa_handler = handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; // Take care of terminated child only
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
        server_error("Sigaction for SIGCHLD error");
    
    // Always listen for new connections from clients
    while (1) {
        // When a new client connect. Open a new socket to communicate with it
        csockfd = accept(ssockfd, (struct sockaddr *) &cli_addr, &socklen);
        if (csockfd < 0)
            server_error("ERROR on accept");
        
        // Create child for this client
        if ((pid = fork()) == 0) {
            // Child
            close(ssockfd); // We dont want this socket in the child
            do_server_processing(csockfd, cli_addr);
            exit(0); // Client exit, terminate child
        
        } else {
            // Parent
            close(csockfd); // Close socket now being used inside the child
        }  
    }
    
    close(ssockfd);
    return (EXIT_SUCCESS);
}


void server_error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


void do_server_processing(int newsockfd, struct sockaddr_in cli_addr)
{
    char buffer[BUFFER_SIZE]; // Send/Receive buffer
    int bytesCount;           // Socket read/write bytes counter
    
    printf(COLOR_CYAN "Client %s connected from remote port %d." COLOR_RESET "\n",
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    
    while (1) {
        // Listening for a message from Client
        memset(&buffer, 0, sizeof(buffer));
        bytesCount = read(newsockfd, buffer, BUFFER_SIZE);
        if (bytesCount < 0) 
            server_error("ERROR reading from socket");

        // Client exit, break loop
        if (bytesCount == 0)
            break;

        // Display what we received from client
        printf(COLOR_RED "[%s:%d -> %d bytes rcvd]: " COLOR_RESET "%s", 
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), bytesCount, buffer);
    }
    
    printf(COLOR_CYAN "Client %s:%d left." COLOR_RESET "\n", 
            inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
}


void handle_sigchld(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0); // Reap all terminated child. Dont hang
}

