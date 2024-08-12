#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void error_handling(char *message) {
    perror(message);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Receiver Port> <Sender Port>\n", argv[0]);
        exit(1);
    }

    int receiver_port = atoi(argv[1]);
    int sender_port = atoi(argv[2]);

    int sock;
    struct sockaddr_in receiver_addr, sender_addr1, sender_addr2;

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        error_handling("socket() error");

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    receiver_addr.sin_port = htons(receiver_port);

    if (bind(sock, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) == -1)
        error_handling("bind() error");

    char buffer[BUFFER_SIZE];
    socklen_t sender_addr1_size = sizeof(sender_addr1);
    socklen_t sender_addr2_size = sizeof(sender_addr2);
    
    while (1) {
        int recv_len = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sender_addr1, &sender_addr1_size);
        buffer[recv_len] = 0;

        if (strcmp(buffer, "exit") == 0)
            break;

        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&sender_addr2, sender_addr2_size);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sock);
    return 0;
}