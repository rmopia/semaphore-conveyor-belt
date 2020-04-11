#include "belt.h"
#include "semaphore.h"
#ifndef CONSUMER_HEADER
#define CONSUMER_HEADER

typedef struct{
    char *Name; /* Ethel, Lucy */
    /* amount of time thread takes to "consume" */
    /* sleep_time could also be empty, thus no wait time */
    int consume_time = 0;
    BeltQueue *BQPtr; /* ptr to conveyor belt queue */
    sem_t *MutexPtr; /* ptr to mutex semaphore addr */
    sem_t *UnconsumedPtr; /* ptr to unconsumed candies semaphore */
    sem_t *AvailablePtr; /* ptr to available space on belt semaphore */
    int *ProdValPtr; /* ptr to total produced amount */
    int *ConsumedValPtr; /* ptr to total consumed amount */
    int *ConsumedFrogPtr; /* ptr to total consumed amount of frogs */
    int *ConsumedEscargotPtr; /* ptr to total consumed amount of escargot */
    int *EscargotBeltPtr;
    int *FrogBeltPtr;
} CONSUMER;

/* consumer process */
void *Consumer(void* voidPtr);

#endif // CONSUMER_HEADER
