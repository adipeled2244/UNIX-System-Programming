#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct philosopher_input
{
    int num_philosopher;
    int *chopsticks;
    int total_philosophers;

} Philosopher_input;

bool takeChopstick(int numC, int numP, int *chopsticks)
{
    printf(" Philosopher number %d : is trying  to take chopstick number: %d\n", numP + 1, numC + 1);
    pthread_mutex_lock(&mutex);
    if (chopsticks[numC] == 0)
    {
        chopsticks[numC] = 1;
        pthread_mutex_unlock(&mutex);

        printf(" Philosopher number %d : has successfully taken chopstick number: %d\n", numP + 1, numC + 1);
        return true;
    }
    pthread_mutex_unlock(&mutex);

    return false;
}

void eat(int numP, int firstChop, int secondChop, int *chopsticks)
{
    int randNum = rand() % 10 + 1; //1-10
    printf(" Philosopher number %d : is eating for %ds\n", numP + 1, randNum);
    sleep(randNum);
    printf(" Philosopher number %d : Finished eating for %ds\n", numP + 1, randNum);

    pthread_mutex_lock(&mutex);
    chopsticks[firstChop] = 0;
    chopsticks[secondChop] = 0;
    pthread_mutex_unlock(&mutex);

    //broacast- tell that philosopher number numP finish to eat 
    pthread_cond_broadcast(&cond);
}

void think(int numP)
{
    int randNum = 10 + rand() % 11; //10-20 (0->10 +10)
    printf(" Philosopher number %d : is thinking for %ds\n", numP + 1, randNum);
    sleep(randNum);
    printf(" Philosopher number %d : Finished thinking for %ds\n", numP + 1, randNum);
}

void *action_of_philosopher(void *p)
{

    Philosopher_input *pi = (Philosopher_input *)p;

    // define priority of the philosopher
    int firstChop, secondChop;
    if (pi->num_philosopher != (pi->total_philosophers - 1))
    {
        firstChop = pi->num_philosopher;
        secondChop = pi->num_philosopher + 1;
    }
    else
    {
        firstChop = 0;
        secondChop = pi->num_philosopher;
    }
    int flag;

    while (1)
    {

        if (takeChopstick(firstChop, pi->num_philosopher, pi->chopsticks))
        {
            flag = 1;
            while (flag)
            {
                if (takeChopstick(secondChop, pi->num_philosopher, pi->chopsticks))
                    flag = 0;

                else
                {
                    pthread_cond_wait(&cond, &mutex);
                    pthread_mutex_unlock(&mutex);
                    // waiting for broadcast
                }
            }

            eat(pi->num_philosopher, firstChop, secondChop, pi->chopsticks);

            think(pi->num_philosopher);
        }

        else
        {
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
            // waiting for broadcast

        }
    }

    free((Philosopher_input *)p);
    return NULL;
}

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    // need to be 2 arguments
    if (argc != 2)
    {
        fprintf(stderr, "You need to send one argument in addition to the name of the program'\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0)
    {
        fprintf(stderr, "You need to send positive number'\n");
        return 1;
    }

    pthread_t *philosophers = (pthread_t *)malloc(n * sizeof(pthread_t));
    if (philosophers == NULL)
    {

        perror("Allocation");
        return 1;
    }

    int *chopsticks = (int *)malloc(n * sizeof(int));
    if (chopsticks == NULL)
    {

        perror("Allocation");
        return 1;
    }
    // intialize chopsticks array with 0
    memset(chopsticks, 0, n * sizeof(int));

    Philosopher_input *pi;

    for (int i = 0; i < n; i++)
    {
        pi = (Philosopher_input *)malloc(sizeof(Philosopher_input));
        pi->chopsticks = chopsticks;
        pi->total_philosophers = n;
        pi->num_philosopher = i;
        if (pthread_create(&philosophers[i], NULL, action_of_philosopher, pi))
            return 1;
        // return 0 if sucess
    }

    for (int i = 0; i < n; i++)
    {
        if (pthread_join(philosophers[i], NULL))
            ;
        return 1;
        // return 0 if sucesss
    }

    return 0;
}
