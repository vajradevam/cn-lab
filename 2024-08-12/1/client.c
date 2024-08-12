#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char r_buffer[BUFFER_SIZE] = {0};
    char s_buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from client";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    while (1) {
        printf("Mark: ");
        fgets(s_buffer, BUFFER_SIZE, stdin);

        send(sock, s_buffer, strlen(s_buffer), 0);
        read(sock, r_buffer, BUFFER_SIZE);

        printf("JPL: %s\n", r_buffer);

        *s_buffer = '\0';
        *r_buffer = '\0';
    }

    close(sock);

    return 0;
}
