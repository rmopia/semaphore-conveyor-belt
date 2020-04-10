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
    int *ConsumedValPtr;
    int *ConsumedFrogPtr;
    int *ConsumedEscargotPtr;
    int *EscargotBeltPtr;
    int *FrogBeltPtr;
} CONSUMER;

void *LucyConsumer(void* voidPtr);
void *EthelConsumer(void* voidPtr);

#endif // CONSUMER_HEADER
