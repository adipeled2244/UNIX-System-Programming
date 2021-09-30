#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
char buf[500000];
int main(void)
{
    int ntowrite, nwrite;
    char *ptr;
    int flags;
    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);
    flags = fcntl(STDOUT_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDOUT_FILENO, F_SETFL, flags);
    ptr = buf;

    while (ntowrite > 0)
    {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr,ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
        if (nwrite > 0)
        {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    fcntl(STDOUT_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    return 0;
}