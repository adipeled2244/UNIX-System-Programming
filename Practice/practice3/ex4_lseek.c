#include <stdio.h>
#include <string.h>
#include <fcntl.h>
char buf1[] = "Hello";
char buf2[] = "World";
int main(int argc, const char *argv[])
{
    int fd;
    if ((fd = open("HoleExample", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
        perror("open");
    if (write(fd, buf1, strlen(buf1)) != strlen(buf1))
        perror("write");
    if (lseek(fd, 20000, SEEK_SET) == -1)
        perror("lseek");
    if (write(fd, buf2, strlen(buf2)) != strlen(buf2))
        perror("write");
    return 0;
}