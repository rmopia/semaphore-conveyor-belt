#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <iostream>
#include <deque>
#include "belt.h"
#include "consumer.h"
#include "producer.h"

using namespace std;

int main(int argc, char **argv){
    sem_t mutex;
    int prod_value = 0;
    int ProductionValue; /* amount of candies produced  */
    int OnBeltValue; /* current amount of candies on the belt */

    BeltQueue *bq = new BeltQueue(10);
    bq->printQueue();

    CONSUMER LucyData;
    pthread_t LucyThread;
    LucyData.Name = "Lucy";
    LucyData.MutexPtr = &mutex;
    LucyData.ProdValPtr = &prod_value;

    PRODUCER FrogData;
    pthread_t FrogThread;
    FrogData.Name = "Crunchy Frog Bite";
    FrogData.MutexPtr = &mutex;
    FrogData.ProdValPtr = &prod_value;

    int Option = 0;

    while ((Option = getopt(argc, argv, "E:L:f:e:")) != -1) {
        switch (Option) {
        case 'E': /* how long to consume via Ethel */
            cout << optarg << endl;
            //IncrementData.N = atoi(optarg);	/* Get value from string */
            break;
        case 'L': /* how long to consume via Lucy */
            cout << optarg << endl;
            LucyData.consume_time = atoi(optarg);
            break;
        case 'f':  /* how long to produce crunchy frog bite */
            cout << optarg << endl;
            FrogData.produce_time = atoi(optarg);
            break;
        case 'e': /* how long to produce everlasting escargo sucker */
            cout << optarg << endl;
            //IncrementData.N = atoi(optarg);
            break;
        default:	/* Handle help & illegal args */
            cout << "Invalid argument found." << endl;
            /* argv[0] - has executable name */
            //printf(USAGE, INCREMENT_TIMES_DEFAULT, DECREMENT_TIMES_DEFAULT);
            exit(1);	/* exit program */
        }
  }

  /* create 1st semaphore */
  if(sem_init(&mutex, 0, 1) == -1){
    exit(1);
  }

  pthread_create(&FrogThread, NULL, FrogProducer, &FrogData);

  pthread_join(FrogThread, NULL);



}
