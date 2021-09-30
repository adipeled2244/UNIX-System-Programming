#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN 256
#define PORT 8080
void write_read(int sockfd)
{
    char buffer[BUF_LEN];
    int n;
    bzero(buffer, BUF_LEN);

    strcpy(buffer, "Hey im client");
    n = write(sockfd, buffer, BUF_LEN);
    if (n < 0)
        perror("write");

    n = read(sockfd, buffer, BUF_LEN);
    if (n < 0)
        perror("read");

    printf("From server: %s\n", buffer);
}

int main(int argc, char const *argv[])
{

    int client_fd;
    struct sockaddr_in server_address, client_address;

    client_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("socket");
        exit(0);
    }

    memset(&client_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        perror("connect");
        exit(0);
    }
    else
        printf("connected to the server\n");

    write_read(client_fd);
    close(client_fd);
}
