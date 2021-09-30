#include <stdio.h>
#include <sys/wait.h>
static void my_sig_int(int sig_number)
{
    printf("You won’t terminate me … \n");
}
int main(int argc, const char *argv[])
{
    if (signal(SIGINT, my_sig_int) == SIG_ERR)
        perror("signal");
    for (;;)
        ;
    return 0;
}