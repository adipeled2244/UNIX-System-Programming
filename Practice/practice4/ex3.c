#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024
int main(int argc, const char *argv[])
{
    int fd, n = 1;
    char buf[SIZE]="adipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledadipeledaaa";
    // memset(buf, '0', 1024);

    // open file to write
    if ((fd = open("adi.txt", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
        perror("open");
    // write 20 b
    if (write(fd, buf, 20) <20)
        return 1;

    close(fd);

    // open file to read
    if ((fd = open("adi.txt", O_RDONLY)) < 0)
        perror("open");


    // read return -1 if fail, 0 if eof
    while (n > 0)
    {
        if ((n = read(fd, buf, SIZE)) < 0)
            perror("read");
        printf("Amount of bytes read = % d\n", n);
    }

    close(fd);

    return 0;
}