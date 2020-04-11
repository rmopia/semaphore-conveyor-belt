#include "belt.h"
#include "semaphore.h"
#ifndef PRODUCER_HEADER
#define PRODUCER_HEADER

typedef struct{
    char *Name; /* frog bite, escargot sucker */
    /* sleep_time could also be empty, thus no wait time */
    int produce_time = 0; /* amount of time thread takes to "produce" */
    BeltQueue *BQPtr; /* ptr to belt queue data structure */
    sem_t *MutexPtr; /* ptr to mutex semaphore */
    sem_t *UnconsumedPtr; /* ptr to unconsumed candies on belt */
    sem_t *AvailablePtr; /* ptr to available space on belt */
    int *ProdValPtr; /* ptr to current total amount of candies produced */
    int *EscargotPtr; /* ptr to total amount of escargot made */
    int *EscargotBeltPtr; /* ptr to escargot amount on belt */
    int *FrogPtr; /* ptr to total amount of frogs made */
    int *FrogBeltPtr; /* ptr to frog amount on belt */
} PRODUCER;

/* producer processes */
void* FrogProducer(void* voidPtr);
void* EscargotProducer(void* voidPtr);

#endif // PRODUCER_HEADER
