#include "semaphore.h"
#ifndef PRODUCER_HEADER
#define PRODUCER_HEADER

typedef struct{
    char *Name; /* frog bite, escargot sucker */
    /* sleep_time could also be empty, thus no wait time */
    int produce_time = 0; /* amount of time thread takes to "produce" */
    sem_t *MutexPtr;
    int *ProdValPtr; /* current total amount of candies produced */
    int *OnBeltPtr; /* current total amount of candies on belt */
} PRODUCER;

void * FrogProducer(void * voidPtr);

#endif // PRODUCER_HEADER
