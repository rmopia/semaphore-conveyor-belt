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
    CONSUMER *ConPtr = (CONSUMER*)(voidPtr);
    while(*(ConPtr->ConsumedValPtr) < 99){
        /* if queue is not empty we proceed */
        if(ConPtr->BQPtr->head != ConPtr->BQPtr->tail){
            //sleep((ConPtr->consume_time)/1000);
            /* we wait for consume time to finish to actually consume */
            Sleep(ConPtr->consume_time);
            /* unconsumed candy on belt goes down */
            sem_wait(ConPtr->UnconsumedPtr);
            sem_wait(ConPtr->MutexPtr); /* mutex down */
            /* if value popped out is a frog */
            if(ConPtr->BQPtr->pop() == FROG){
                /* increment/decrement required data in struct */
                *(ConPtr->ConsumedFrogPtr) += 1;
                *(ConPtr->FrogBeltPtr) -= 1;
                *(ConPtr->ConsumedValPtr) += 1;

                /* output of what's been produced and what's on the belt */
                /* as well as who just consumed a candy */
                cout << "Belt: " << *(ConPtr->FrogBeltPtr) << " frogs + " <<
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
                cout << "Belt: " << *(ConPtr->FrogBeltPtr) << " frogs + " <<
                *(ConPtr->EscargotBeltPtr) << " escargots = " <<
                *(ConPtr->FrogBeltPtr) + *(ConPtr->EscargotBeltPtr) <<
                ". produced: " << *(ConPtr->ProdValPtr) << "\t" <<
                (ConPtr->Name) << " consumed escargot sucker" <<
                ".\n" << flush;
            }
            sem_post(ConPtr->MutexPtr); /* mutex up */
            sem_post(ConPtr->AvailablePtr); /* space on queue goes up */
        }
    }
}
