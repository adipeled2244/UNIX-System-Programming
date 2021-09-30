#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 1024
int main(int argc, const char *argv[])
{
    int n;
    char buffer[BUF_SIZE];
    while ((n = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
        if (write(STDOUT_FILENO, buffer, n) != n)
            return 1;
    if (n < 0)
        return 2;
    return 0;
}

