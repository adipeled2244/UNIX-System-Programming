#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


// calculate how many space in order to make space
int calcRemaining(int x)
{
    int sum = 0;
    for (int i = 1; i < x; i++)
    {
        sum += i;
    }
    return sum;
}

// calculate offset from the begining of the file in order to begin to write
int calcOffset(int x, int n)
{
    int sum = 0;
    for(; n <= x; ++n)
    {
        sum += n/2+n%2;
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    char x;
    scanf("%c", &x);
    char number = x;
    int fd = open("my_exercise.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open my_exercise");
        exit(1);
    }

    for(int i; number > '0'; --number)
    {
        for (i = (number-'0'); i > (number-'0')/2; --i)
        {
            write(fd, &number, 1);
        }
        lseek(fd, calcRemaining(number-'0'), SEEK_CUR);
        for (; i > 0; --i)
        {
            write(fd, &number, 1);
        }
        lseek(fd, calcOffset(x-'0', number-'0'), SEEK_SET);
    }

    close(fd);
    return 0;
}