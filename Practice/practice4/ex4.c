

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int fd;
    int out_fd;
    char *path = "/.";
    out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
    if (out_fd < 0)
        perror("open");
    if (close(STDOUT_FILENO) < 0)
        perror("close");
    fd = dup(out_fd);
    if (fd != STDOUT_FILENO)
        return 1;
    puts("My Message\n");

    return 0;
}
