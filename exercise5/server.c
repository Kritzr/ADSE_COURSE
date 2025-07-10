#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//for standard io and memory functions
#include <unistd.h>
#include <netinet/in.h>
//for unix systems calls like (read(), write(), close), and the other is for the network structs and htons(), socket address
#define port 8080
#define bs 1024

int main() {
    int server_fd, client_socket;//file descritptor
    struct sockaddr_in address;//ip+port info
    int addrlen = sizeof(address);
    char buffer[bs] = {0};
    char *response = "message received by server.";

    // create socket for AF_INET ->IPV4,  sockstream - tcp, and 0 protocol for tcp
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // bind socket to port - htons(): Converts port from host to network byte order (big-endian)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    // accept a connection
    if ((client_socket = accept(server_fd, (struct sockaddr*)&address,
                                (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    read(client_socket, buffer, bs);
    printf("Received from client: %s\n", buffer);

    send(client_socket, response, strlen(response), 0);
    printf("Response sent to client.\n");

    close(client_socket);
    close(server_fd);
    return 0;
}
