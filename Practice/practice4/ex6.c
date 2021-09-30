#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 4096
int main (int argc, const char* argv[])
{
// …
int socket ;
// …
int fd, i;
char buf[SIZE];
fd = open(filepath, O_RDONLY);
do
{
int n_read = read(fd, buf, SIZE);
for (i = 0; i < nread; i += nwrite)
{
nwrite = write(socket, buf + i, n_read – i);
}
} while (n_read != 0);
return 0;
}
