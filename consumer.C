#include <unistd.h>
#include <semaphore.h>
#include <windows.h>
#include <iostream>
#include "consumer.h"
#include "belt.h"

using namespace std;

/* both Ethel and Lucy use this process but in separate threads */
void *Consumer(void* voidPtr){
    /* convert void pointer for data use and collection */
    CONSUMER *ConPtr = (CONSUMER*)(voidPtr);
    /* we consume 100 candies before we finish the threads */
    while(*(ConPtr->ConsumedValPtr) < 100){
        /* if queue is not empty we proceed */
        if(ConPtr->BQPtr->head != ConPtr->BQPtr->tail){
            /* unconsumed candy on belt sem val goes down */
            /* trywait helps prevent overlap and thus deadlock */
            if(sem_trywait(ConPtr->UnconsumedPtr) == 0){
                sem_wait(ConPtr->MutexPtr); /* mutex down */
                /* if value popped out is a frog */
                if(ConPtr->BQPtr->pop() == FROG){
                    /* increment/decrement required data in struct */
                    *(ConPtr->ConsumedFrogPtr) += 1;
                    *(ConPtr->FrogBeltPtr) -= 1;
                    *(ConPtr->ConsumedValPtr) += 1;

                    /* output of what's been produced and what's on the belt */
                    /* as well as who just consumed a candy */
                    cout << "Belt: " << *(ConPtr->FrogBeltPtr) <<" frogs + " <<
                    *(ConPtr->EscargotBeltPtr) << " escargots = " <<
                    *(ConPtr->FrogBeltPtr) + *(ConPtr->EscargotBeltPtr) <<
                    ". produced: " << *(ConPtr->ProdValPtr) << "\t" <<
                    (ConPtr->Name) << " consumed crunchy frog bite" <<
                    ".\n" << flush;
                }
                /* else the value popped out is an escargot */
                else{
                    /* update escargot associated data */
                    *(ConPtr->ConsumedEscargotPtr) += 1;
                    *(ConPtr->EscargotBeltPtr) -= 1;
                    *(ConPtr->ConsumedValPtr) += 1;

                    /* output of belt */
                    cout << "Belt: " << *(ConPtr->FrogBeltPtr) <<" frogs + " <<
                    *(ConPtr->EscargotBeltPtr) << " escargots = " <<
                    *(ConPtr->FrogBeltPtr) + *(ConPtr->EscargotBeltPtr) <<
                    ". produced: " << *(ConPtr->ProdValPtr) << "\t" <<
                    (ConPtr->Name) << " consumed escargot sucker" <<
                    ".\n" << flush;
                }
                sem_post(ConPtr->MutexPtr); /* mutex up, exit */
                sem_post(ConPtr->AvailablePtr); /* space on queue goes up */
                /* milliseconds converted to seconds since */
                /* unistd sleep only takes in seconds */
                //sleep((ConPtr->consume_time)/1000);
                Sleep(ConPtr->consume_time);
            }
        }
    }
}
