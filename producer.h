#include "belt.h"
#include "semaphore.h"
#ifndef PRODUCER_HEADER
#define PRODUCER_HEADER

typedef struct{
    char *Name; /* frog bite, escargot sucker */
    /* sleep_time could also be empty, thus no wait time */
    int produce_time = 0; /* amount of time thread takes to "produce" */
    BeltQueue *BQPtr;
    sem_t *MutexPtr;
    sem_t *UnconsumedPtr;
    sem_t *AvailablePtr;
    int *ProdValPtr; /* current total amount of candies produced */
    int *EscargotPtr;
    int *EscargotBeltPtr;
    int *FrogPtr;
    int *FrogBeltPtr;
} PRODUCER;

void* FrogProducer(void* voidPtr);
void* EscargotProducer(void* voidPtr);

#endif // PRODUCER_HEADER
