#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <iostream>
#include "belt.h"
#include "consumer.h"
#include "producer.h"

using namespace std;

int main(int argc, char **argv){
    sem_t mutex; /* basic Dijkstra semaphore used in threads */
    sem_t unconsumed; /* current space taken up on conveyor belt */
    sem_t available_slots; /* current available space on conveyor belt */
    int total_produced = 0; /* total amount of candies produced */
    int total_frogs = 0; /* total amount of frogs produced */
    int total_escargot = 0; /* total amount of escargot produced */
    int frogs_on_belt = 0; /* total amount of frogs currently on queue */
    int escargot_on_belt = 0; /* total amount of escargot currently on queue */
    int total_consumed = 0; /* of the 1-100, how many are currently consumed */

    /* conveyor belt only has space for 10 candies maximum */
    BeltQueue *bq = new BeltQueue(10);

    int l_frog_consumed = 0; /* amount of frogs lucy consumes */
    int l_escargot_consumed = 0; /* amount of escargot lucy consumes */
    CONSUMER LucyData;
    pthread_t LucyThread;
    LucyData.Name = "Lucy";
    LucyData.MutexPtr = &mutex;
    LucyData.UnconsumedPtr = &unconsumed;
    LucyData.AvailablePtr = &available_slots;
    LucyData.ProdValPtr = &total_produced;
    LucyData.ConsumedValPtr = &total_consumed;
    LucyData.ConsumedFrogPtr = &l_frog_consumed;
    LucyData.ConsumedEscargotPtr = &l_escargot_consumed;
    LucyData.FrogBeltPtr = &frogs_on_belt;
    LucyData.EscargotBeltPtr = &escargot_on_belt;
    LucyData.BQPtr = bq;

    int e_frog_consumed = 0; /* amount of frogs ethel consumes */
    int e_escargot_consumed = 0; /* amount of escargot ethel consumes */
    CONSUMER EthelData;
    pthread_t EthelThread;
    EthelData.Name = "Ethel";
    EthelData.MutexPtr = &mutex;
    EthelData.UnconsumedPtr = &unconsumed;
    EthelData.AvailablePtr = &available_slots;
    EthelData.ProdValPtr = &total_produced;
    EthelData.ConsumedValPtr = &total_consumed;
    EthelData.ConsumedFrogPtr = &e_frog_consumed;
    EthelData.ConsumedEscargotPtr = &e_escargot_consumed;
    EthelData.FrogBeltPtr = &frogs_on_belt;
    EthelData.EscargotBeltPtr = &escargot_on_belt;
    EthelData.BQPtr = bq;

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
    EscargotData.Name = "escargot sucker";
    EscargotData.MutexPtr = &mutex;
    EscargotData.UnconsumedPtr = &unconsumed;
    EscargotData.AvailablePtr = &available_slots;
    EscargotData.ProdValPtr = &total_produced;
    EscargotData.FrogPtr = &total_frogs;
    EscargotData.FrogBeltPtr = &frogs_on_belt;
    EscargotData.EscargotPtr = &total_escargot;
    EscargotData.EscargotBeltPtr = &escargot_on_belt;
    EscargotData.BQPtr = bq;

    int Option = 0; /* flags declared by user in command line */

    while ((Option = getopt(argc, argv, "E:L:f:e:")) != -1) {
        switch (Option) {
        case 'E': /* how long it takes Ethel to consume 1 candy */
            EthelData.consume_time = atoi(optarg);
            break;
        case 'L': /* how long it takes Lucy to consume 1 candy */
            LucyData.consume_time = atoi(optarg);
            break;
        case 'f':  /* how long to produce a crunchy frog bite */
            FrogData.produce_time = atoi(optarg);
            break;
        case 'e': /* how long to produce a everlasting escargot sucker */
            EscargotData.produce_time = atoi(optarg);
            break;
        default: /* deals with invalid args from user */
            cout << "Invalid argument found." << endl;
            exit(1); /* exits program */
        }
  }

    /* traditional Dijkstra wait/signal semaphore */
    if(sem_init(&mutex, 0, 1) == -1){
        exit(1); /* exit if initialization goes wrong */
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
    pthread_create(&EscargotThread, NULL, EscargotProducer, &EscargotData);

    /* consumer threads */
    pthread_create(&LucyThread, NULL, Consumer, &LucyData);
    pthread_create(&EthelThread, NULL, Consumer, &EthelData);

    /* main thread waits for following threads to complete */
    pthread_join(FrogThread, NULL);
    pthread_join(EscargotThread, NULL);
    pthread_join(LucyThread, NULL);
    pthread_join(EthelThread, NULL);

    cout << endl;
    cout << "PRODUCTION REPORT" << endl;
    for(int i = 0; i < 40; i++){
        cout << "-";
    }
    cout << endl;
    /* Amount of candy produced by Frog producer */
    cout << FrogData.Name << " producer generated "
    << *(FrogData.FrogPtr) << " candies" << endl;

    /* Amount of candy produced by Escargot producer */
    cout << EscargotData.Name << " producer generated "
    << *(EscargotData.EscargotPtr) << " candies" << endl;

    /* Amount of candy consumed by Lucy */
    cout << LucyData.Name << " consumed " << *(LucyData.ConsumedFrogPtr) <<
    " crunchy frog bites + " << *(LucyData.ConsumedEscargotPtr) <<
    " escargot suckers = " << *(LucyData.ConsumedFrogPtr) +
    *(LucyData.ConsumedEscargotPtr) << endl;
    /* Amount of candy consumed by Ethel */
    cout << EthelData.Name << " consumed " << *(EthelData.ConsumedFrogPtr) <<
    " crunchy frog bites + " << *(EthelData.ConsumedEscargotPtr) <<
    " escargot suckers = " << *(EthelData.ConsumedFrogPtr) +
    *(EthelData.ConsumedEscargotPtr) << endl;

}
