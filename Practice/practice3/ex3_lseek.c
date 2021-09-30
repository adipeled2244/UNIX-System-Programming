#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("File is not capable of seeking.\n");
    else
        printf("File is capable of seeking.\n");
    return 0;
}