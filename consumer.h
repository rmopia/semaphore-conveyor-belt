#ifndef CONSUMER_HEADER
#define CONSUMER_HEADER

typedef struct{
    char *Name; /* Ethel, Lucy */
    /* sleep_time could also be empty, thus no wait time */
    int consume_time; /* amount of time thread takes to "consume" */
    sem_t *SemPtr;
    int *ProdValPtr; /* current total amount of candies produced */
    int *OnBeltPtr; /* current total amount of candies on belt */
} CONSUMER;

#endif // CONSUMER_HEADER
