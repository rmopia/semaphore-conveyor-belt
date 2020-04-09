#include "belt.h"
#include "semaphore.h"
#ifndef CONSUMER_HEADER
#define CONSUMER_HEADER

typedef struct{
    char *Name; /* Ethel, Lucy */
    /* sleep_time could also be empty, thus no wait time */
    int consume_time = 0; /* amount of time thread takes to "consume" */
    BeltQueue *BQPtr;
    sem_t *MutexPtr;
    sem_t *UnconsumedPtr;
    sem_t *AvailablePtr;
    int *ProdValPtr; /* current total amount of candies produced */
    int *ConsumedValPtr;
    int *ConsumedFrogPtr;
    int *ConsumedEsacrgotPtr;
    int *EscargotPtr;
    int *FrogPtr;
    int *FrogBeltPtr;
    //int *OnBeltPtr; /* current total amount of candies on belt */
} CONSUMER;

void *LucyConsumer(void* voidPtr);

#endif // CONSUMER_HEADER
