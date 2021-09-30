#include <stdio.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
    int ch;
    while ((ch = getc(stdin)) != EOF)
        if (putc(ch, stdout) == EOF)
            return 1;
    if (ferror(stdin))
        return 2;
    return 0;
}