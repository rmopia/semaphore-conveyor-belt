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

    BeltQueue *bq = new BeltQueue(10);
    bq->push(2);
    bq->push(3);
    bq->push(4);
    cout << bq->max_len << endl;
    cout << bq->pop() << endl;

    CONSUMER LucyData;
    pthread_t LucyThread;

    PRODUCER FrogData;
    pthread_t FrogThread;

    sem_t mutex;
    int ProductionValue; /* amount of candies produced  */
    int OnBeltValue; /* current amount of candies on the belt */

    int Option = 0;

    while ((Option = getopt(argc, argv, "E:L:f:e:")) != -1) {
        switch (Option) {
        case 'E': /* how long to consume via Ethel */
            cout << optarg << endl;
            //IncrementData.N = atoi(optarg);	/* Get value from string */
            break;
        case 'L': /* how long to consume via Lucy */
            cout << optarg << endl;
            //DecrementData.N = atoi(optarg);
            break;
        case 'f':  /* how long to produce crunchy frog bite */
            cout << optarg << endl;
            //IncrementData.N = atoi(optarg);	/* Get value from string */
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
}
