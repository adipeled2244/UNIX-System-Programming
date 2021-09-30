#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

static int counter = 0;

static void signals_handler(int sig_number)
{
    counter--;
    printf("You won’t terminate me … %d \n ", counter);
}
int main(int argc, const char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "you need to send argument'\n");
        return 1;
    }
    char *p;
    counter = strtol(argv[1], &p, 10);
    
    if (signal(SIGINT, signals_handler) == SIG_ERR)
    {
        perror("signal");
    }
    while (counter != 0){}

    return 0;
}
