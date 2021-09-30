#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int r;
    if ((r = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
        perror("fcntl");
    switch (r & O_ACCMODE)
    {
    case O_RDONLY:
        printf("ReadOnly\n");
        break;
    case O_WRONLY:
        printf("WriteOnly\n");
        break;
    case O_RDWR:
        printf("ReadWrite\n");
        break;
    }
    return 0;
}
