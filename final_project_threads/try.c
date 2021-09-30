#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void * action(void * p){
    for (int i = 0; true ; i++)
    {
        printf("%d",i);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    pthread_t tr ;
    pthread_create(&tr,NULL,action,NULL);
    pthread_join(tr,NULL);
    return 0;
}
