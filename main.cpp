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
    sem_t unconsumed; /* current space taken up on conveyor belt */
    sem_t available_slots; /* current available space on conveyor belt */
    int total_produced = 0; /* total amount of candies produced */
    int total_frogs = 0;
    int total_escargot = 0;
    int frogs_on_belt = 0;
    int escargot_on_belt = 0;
    int total_consumed = 0; /* of the 1-100, how many are currently consumed */

    BeltQueue *bq = new BeltQueue(10);
    bq->printQueue();

    CONSUMER LucyData;
    pthread_t LucyThread;
    int l_frog_consumed = 0;
    int l_escargot_consumed = 0;
    LucyData.Name = "Lucy";
    LucyData.MutexPtr = &mutex;
    LucyData.UnconsumedPtr = &unconsumed;
    LucyData.AvailablePtr = &available_slots;
    LucyData.ConsumedValPtr = &total_consumed;
    LucyData.ConsumedFrogPtr = &l_frog_consumed;
    LucyData.ConsumedEsacrgotPtr = &l_escargot_consumed;
    LucyData.ProdValPtr = &total_produced;
    LucyData.FrogPtr = &total_frogs;
    LucyData.FrogBeltPtr = &frogs_on_belt;
    LucyData.BQPtr = bq;

    PRODUCER FrogData;
    pthread_t FrogThread;
    FrogData.Name = "crunchy frog bite";
    FrogData.MutexPtr = &mutex;
    FrogData.UnconsumedPtr = &unconsumed;
    FrogData.AvailablePtr = &available_slots;
    FrogData.ProdValPtr = &total_produced;
    FrogData.FrogPtr = &total_frogs;
    FrogData.FrogBeltPtr = &frogs_on_belt;
    FrogData.EscargotPtr = &total_escargot;
    FrogData.EscargotBeltPtr = &escargot_on_belt;
    FrogData.BQPtr = bq;

    PRODUCER EscargotData;
    pthread_t EscargotThread;
    EscargotData.Name = "everlasting escargot sucker";
    EscargotData.MutexPtr = &mutex;
    EscargotData.UnconsumedPtr = &unconsumed;
    EscargotData.AvailablePtr = &available_slots;
    EscargotData.ProdValPtr = &total_produced;
    EscargotData.FrogPtr = &total_frogs;
    EscargotData.FrogBeltPtr = &frogs_on_belt;
    EscargotData.EscargotPtr = &total_escargot;
    EscargotData.EscargotBeltPtr = &escargot_on_belt;
    EscargotData.BQPtr = bq;

    int Option = 0;

    while ((Option = getopt(argc, argv, "E:L:f:e:")) != -1) {
        switch (Option) {
        case 'E': /* how long it takes Ethel to consume 1 candy */
            cout << optarg << endl;
            /*********************************************************************************/
            break;
        case 'L': /* how long it takes Lucy to consume 1 candy */
            cout << optarg << endl;
            LucyData.consume_time = atoi(optarg);
            break;
        case 'f':  /* how long to produce a crunchy frog bite */
            cout << optarg << endl;
            FrogData.produce_time = atoi(optarg);
            break;
        case 'e': /* how long to produce a everlasting escargot sucker */
            cout << optarg << endl;
            EscargotData.produce_time = atoi(optarg);
            break;
        default: /* deals with invalid args from user */
            cout << "Invalid argument found." << endl;
            exit(1); /* exits program */
        }
  }

    /* create 1st semaphore */
    if(sem_init(&mutex, 0, 1) == -1){
        exit(1);
    }

    /* following semaphores follow a ratio of 0:10 i.e. 3 unconsumed:7 slots */
    if(sem_init(&unconsumed, 0, 0) == -1){
        exit(1);
    }

    if(sem_init(&available_slots, 0, bq->max_len) == -1){
        exit(1);
    }

    /* producer threads */
    pthread_create(&FrogThread, NULL, FrogProducer, &FrogData);

    /* consumer threads */
    pthread_create(&LucyThread, NULL, LucyConsumer, &LucyData);

    pthread_join(FrogThread, NULL);
    pthread_join(LucyThread, NULL);

    cout << endl;
    cout << "PRODUCTION REPORT" << endl;
    for(int i = 0; i < 40; i++){
    cout << "-";
    }
    cout << endl;
    cout << FrogData.Name << " producer generated " << *(FrogData.FrogPtr) << " candies" << endl;
    cout << endl;
    cout << LucyData.Name << " consumed " << *(LucyData.ConsumedFrogPtr) << " " << FrogData.Name << "s + " << endl;

}
