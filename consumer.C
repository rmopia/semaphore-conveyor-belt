#include <unistd.h>
#include <windows.h>
#include <semaphore.h>
#include <iostream>
#include "consumer.h"
#include "belt.h"

using namespace std;

/* both Ethel and Lucy use this process but in separate threads */
void *Consumer(void* voidPtr){
    /* convert pointer for data use */
    CONSUMER *dataPtr = (CONSUMER*)(voidPtr);
    while(*(dataPtr->ConsumedValPtr) < 100){
        /* if queue is not empty we proceed */
        if(dataPtr->BQPtr->head != dataPtr->BQPtr->tail){
            //sleep((dataPtr->consume_time)/1000);
            Sleep(dataPtr->consume_time);
            /* unconsumed candy on belt goes down */
            sem_wait(dataPtr->UnconsumedPtr);
            sem_wait(dataPtr->MutexPtr); /* mutex down */
            /* if value popped out is a frog */
            if(dataPtr->BQPtr->pop() == FROG){
                /* increment/decrement required data in struct */
                *(dataPtr->ConsumedFrogPtr) += 1;
                *(dataPtr->FrogBeltPtr) -= 1;
                *(dataPtr->ConsumedValPtr) += 1;

                /* output of what's been produced and what's on the belt */
                /* as well as who just consumed a candy */
                cout << "Belt: " << *(dataPtr->FrogBeltPtr) << " frogs + " <<
                *(dataPtr->EscargotBeltPtr) << " escargots = " <<
                *(dataPtr->FrogBeltPtr) + *(dataPtr->EscargotBeltPtr) <<
                ". produced: " << *(dataPtr->ProdValPtr) << "\t" <<
                (dataPtr->Name) << " consumed crunchy frog bite" <<
                ".\n" << flush;
            }
            /* if value popped out is an escargot */
            else{
                *(dataPtr->ConsumedEscargotPtr) += 1;
                *(dataPtr->EscargotBeltPtr) -= 1;
                *(dataPtr->ConsumedValPtr) += 1;

                cout << "Belt: " << *(dataPtr->FrogBeltPtr) << " frogs + " <<
                *(dataPtr->EscargotBeltPtr) << " escargots = " <<
                *(dataPtr->FrogBeltPtr) + *(dataPtr->EscargotBeltPtr) <<
                ". produced: " << *(dataPtr->ProdValPtr) << "\t" <<
                (dataPtr->Name) << " consumed escargot sucker" <<
                ".\n" << flush;
            }
            sem_post(dataPtr->MutexPtr); /* mutex up */
            sem_post(dataPtr->AvailablePtr); /* space on queue goes up */
        }
    }
}
