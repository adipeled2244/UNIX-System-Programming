#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define SIZE 1024
int main(int argc, const char *argv[])
{
    int fd, n;
    char buf[SIZE];
    if ((fd = open("AFile.txt", O_RDONLY)) < 0)
        perror("open");
    if ((n = read(fd, buf, SIZE)) < 0)
        perror("read");
    printf("Amount of bytes read = % d\n", n);
    if ((n = read(fd, buf, SIZE)) < 0)
        perror("read");
    printf("Amount of bytes read = % d\n", n);
    return 0;
}