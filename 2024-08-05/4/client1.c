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
    if (argc != 4) {
        printf("Usage: %s <Receiver IP> <Receiver Port> <Sender Port>\n", argv[0]);
        exit(1);
    }

    char *receiver_ip = argv[1];
    int receiver_port = atoi(argv[2]);
    int sender_port = atoi(argv[3]);

    int sock;
    struct sockaddr_in sender_addr, receiver_addr;

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        error_handling("socket() error");

    memset(&sender_addr, 0, sizeof(sender_addr));
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sender_addr.sin_port = htons(sender_port);

    if (bind(sock, (struct sockaddr *)&sender_addr, sizeof(sender_addr)) == -1)
        error_handling("bind() error");

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(receiver_ip);
    receiver_addr.sin_port = htons(receiver_port);


    char buffer[BUFFER_SIZE];

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove the newline character

        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

        if (strcmp(buffer, "exit") == 0)
            break;

        int recv_len = recvfrom(sock, buffer, BUFFER_SIZE, 0, NULL, NULL);
        buffer[recv_len] = 0;
        printf("%s\n", buffer);
    }

    close(sock);
    return 0;
}