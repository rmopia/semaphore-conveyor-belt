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
    int *EscargoPtr;
    int *FrogPtr;
    //int *OnBeltPtr; /* current total amount of candies on belt */
} CONSUMER;

#endif // CONSUMER_HEADER
