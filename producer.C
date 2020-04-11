#include <unistd.h>
#include <windows.h>
#include <semaphore.h>
#include <iostream>
#include "producer.h"
#include "belt.h"

using namespace std;

void* FrogProducer(void* voidPtr){
    /* convert void ptr to a producer ptr to use data */
    PRODUCER *dataPtr = (PRODUCER*)(voidPtr);
    while(*(dataPtr->ProdValPtr) < 100){
        /* only 3 frog bits allowed on belt at a time b/c expensive */
        if(*(dataPtr->FrogBeltPtr) < 3){
            // change sleep timer to nanosleep when we move code //
            /*******************************************/
            Sleep(dataPtr->produce_time); // 1000ms = 1s
            /*******************************************/

            sem_wait(dataPtr->AvailablePtr); /* conveyor belt slots down */
            sem_wait(dataPtr->MutexPtr); /* mutex down */

            /* frog added to queue */
            dataPtr->BQPtr->push(FROG);
            /* associated frog data is filled in */
            *(dataPtr->ProdValPtr) += 1;
            *(dataPtr->FrogPtr) += 1;
            *(dataPtr->FrogBeltPtr) += 1;

            /* output of what's been produced and what's on the belt */
            /* as well as what was just produced */
            cout << "Belt: " << *(dataPtr->FrogBeltPtr) << " frogs + " <<
             *(dataPtr->EscargotBeltPtr) << " escargots = " <<
             *(dataPtr->FrogBeltPtr) + *(dataPtr->EscargotBeltPtr) <<
             ". produced: " << *(dataPtr->ProdValPtr) << "\tAdded " <<
              dataPtr->Name << ".\n" << flush;

            sem_post(dataPtr->MutexPtr); /* mutex up */
            sem_post(dataPtr->UnconsumedPtr); /* candy on belt up */
        }
        else{
            continue;
        }
    }
}

void* EscargotProducer(void* voidPtr){
    PRODUCER *dataPtr = (PRODUCER*)(voidPtr);
    while(*(dataPtr->ProdValPtr) < 100){
        /* no particular limit on escargot suckers */
        if((*(dataPtr->FrogBeltPtr) == 3 && *(dataPtr->EscargotBeltPtr) < 7)||
        ((*(dataPtr->FrogBeltPtr) == 2 && *(dataPtr->EscargotBeltPtr) < 8))||
        ((*(dataPtr->FrogBeltPtr) == 1 && *(dataPtr->EscargotBeltPtr) < 9))||
        ((*(dataPtr->FrogBeltPtr) == 0 && *(dataPtr->EscargotBeltPtr) < 10))){
            // change sleep timer to nanosleep when we move code //
            /*******************************************/
            Sleep(dataPtr->produce_time); // 1000ms = 1s
            /*******************************************/

            sem_wait(dataPtr->AvailablePtr); /* conveyor belt slots down */
            sem_wait(dataPtr->MutexPtr); /* mutex down */

            /* add an escargot to the queue */
            dataPtr->BQPtr->push(ESCARGOT);
            /* fill in associated escargot data */
            *(dataPtr->ProdValPtr) += 1;
            *(dataPtr->EscargotPtr) += 1;
            *(dataPtr->EscargotBeltPtr) += 1;

            /* output of what's been produced and what's on the belt */
            cout << "Belt: " << *(dataPtr->FrogBeltPtr) << " frogs + " <<
             *(dataPtr->EscargotBeltPtr) << " escargots = " <<
             *(dataPtr->FrogBeltPtr) + *(dataPtr->EscargotBeltPtr) <<
             ". produced: " << *(dataPtr->ProdValPtr) << "\tAdded " <<
              dataPtr->Name << ".\n" << flush;

            sem_post(dataPtr->MutexPtr); /* mutex up */
            sem_post(dataPtr->UnconsumedPtr); /* unconsumed candy on belt up */
        }
        else{
            continue;
        }
    }
}
