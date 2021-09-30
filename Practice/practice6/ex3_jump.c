#include <setjmp.h>
#include <stdio.h>
jmp_buf jmp_buffer;
static void foo(void)
{
    longjmp(jmp_buffer, 1);
}
int main(void)
{
    char line[1024];
    int x = 5, y = 6, z = 7;
    printf("Before x=%d,y=%d,z=%d\n", x, y, z);
    if (setjmp(jmp_buffer) != 0)
    {
        printf("After x=%d,y=%d,z=%d\n", x, y, z);
        return 1;
    }
    ++x;
    ++y;
    ++z;
    foo();
    return 0;
}