#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
#define SIZE 3

int main(int argc, char const *argv[])
{

    int *pid_arr = mmap(NULL, SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (pid_arr == NULL)
        perror("cannot allocate");

    pid_t pid;

    int counter = 0;

    while (counter < SIZE)
    {
        if ((pid = fork()) < 0)
            perror("fork error");

        else if (pid == 0) //child
        {

            pid_arr[counter] = getpid();
            exit(1);
        }

        else //parent
        {
            int status;
            if ((pid = waitpid(pid, &status, 0) < 0))
                perror("waitpid");
        }

        counter++;
    }

    if (counter == SIZE)
    {

        printf("Pid's array: ");

        printf("[");

        for (int i = 0; i < SIZE; i++)
        {

            printf("%d", pid_arr[i]);
            if (i != 2)
                printf(", ");
        }

        printf("]\n");
    }

    munmap(pid_arr,SIZE*sizeof(int));
    return 0;
}