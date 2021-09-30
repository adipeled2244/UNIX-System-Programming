#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_LEN 256
#define PORT 8080
void read_write(int sockfd)
{
    char buffer[BUF_LEN];
    int n;
    bzero(buffer, BUF_LEN);

    n = read(sockfd, buffer, BUF_LEN);
    if (n < 0)
        perror("read");

    printf("From client: %s\n", buffer);

    strcpy(buffer, "Hey im server");
    n = write(sockfd, buffer, BUF_LEN);
    if (n < 0)
        perror("write");
}

int main(int argc, char const *argv[])
{
    int server_fd, to_socket;
    struct sockaddr_in server_address, client_address;

    server_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket");
        exit(0);
    }


    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        perror("bind");
        exit(0);
    }

    if (listen(server_fd, 3) != 0)
    {
        perror("listen");
        exit(0);
    }
    else
        printf("server listen...\n");

    int len = sizeof(client_address);
    to_socket = accept(server_fd, (struct sockaddr *)&client_address, &len);
    if (to_socket < 0)
    {
        perror("accept");
        exit(0);
    }
    else
        printf("server accepted the client\n");

    read_write(to_socket);
    close(to_socket);
    close(server_fd);

    return 0;
}
