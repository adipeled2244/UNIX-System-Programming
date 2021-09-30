#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main(int argc, const char *argv[])
{
        printf("%s\n", getenv("HOME"));
        printf("%s\n", getenv("PWD"));
    // printf("HOME:%s\n", getenv("HOME"));
    return 0;
}