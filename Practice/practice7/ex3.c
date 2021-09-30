#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// producer - add to queue and make signal
void push_message(struct MsgItem *item)
{
    pthread_mutex_lock(&qlock);
    queue->tail->next = item;
    queue->tail = item;
    pthread_cond_signal(&qcond);
    pthread_mutex_unlock(&qlock);
}

// consumer - remove from queue and make wait
void pop_message(void)
{
    struct MsgItem *item;
    for (;;)
    {
        pthread_mutex_lock(&qlock);
        while (queue->head == NULL)
            pthread_cond_wait(&qcond,&qlock);
        item = queue->head;
        queue->head = queue->head -> next;
        pthread_mutex_unlock(&qlock);
    }
}

struct MsgItem
{
    void *data;
    struct MsgItem *next;
};
struct MsgQueue
{
    struct MsgItem *head;
    struct MsgItem *tail;
};

struct MsgQueue *queue;
pthread_cond_t qcond =PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock =PTHREAD_MUTEX_INITIALIZER;