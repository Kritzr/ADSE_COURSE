#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define port 8080
#define bs 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hola from client krithika!";
    char buffer[bs] = {0};

    // create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // convert IPv4 address to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address / Address not supported\n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }

    send(sock, message, strlen(message), 0);
    printf("Message sent to server.\n");

    read(sock, buffer, bs);
    printf("Response from server: %s\n", buffer);

    close(sock);
    return 0;
}
