#ifndef PRODUCER_HEADER
#define PRODUCER_HEADER

typedef struct{
    char *Name; /* frog bite, escargot sucker */
    /* sleep_time could also be empty, thus no wait time */
    int consume_time; /* amount of time thread takes to "consume" */
    sem_t *SemPtr;
    int *ProdValPtr; /* current total amount of candies produced */
    int *OnBeltPtr; /* current total amount of candies on belt */
} PRODUCER;

#endif // PRODUCER_HEADER
