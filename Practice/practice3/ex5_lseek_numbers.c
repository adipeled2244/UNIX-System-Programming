#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{

    int number;
    fscanf(stdin, "%d", &number);
    int fd;

    if ((fd = open("res.out", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
    {
        perror("open");
    }

    int counter = 0;
    int limit = number;
    char str_num[3];

    for (int i = limit; i > 0; i++)
    {
        sprintf(str_num, "%d", number);
        lseek(fd, counter / 2, SEEK_CUR);

        for (int j = 0; j < number; j++)
        {
            write(fd, str_num, strlen(str_num));
            counter++;
        }
        number--;
    }
}
