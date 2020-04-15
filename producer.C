#include <unistd.h>
#include <semaphore.h>
#include <windows.h>
#include <iostream>
#include "producer.h"
#include "belt.h"

using namespace std;

/* func that increments frog candy on the belt queue */
void* FrogProducer(void* voidPtr){
    /* convert void ptr to a producer ptr to use/collect data */
    PRODUCER *FrgPtr = (PRODUCER*)(voidPtr);
    /* only produce until 100 candy mark */
    while(*(FrgPtr->ProdValPtr) < 100){
        /* only 3 frog bits allowed on belt at a time b/c they're expensive */
        if(*(FrgPtr->FrogBeltPtr) < 3){
            sem_wait(FrgPtr->AvailablePtr); /* conveyor belt slots down */
            sem_wait(FrgPtr->MutexPtr); /* mutex down */

            /* frog added to queue */
            FrgPtr->BQPtr->push(FROG);
            /* associated frog data is updated */
            *(FrgPtr->ProdValPtr) += 1;
            *(FrgPtr->FrogPtr) += 1;
            *(FrgPtr->FrogBeltPtr) += 1;

            /* output of what's been produced and what's on the belt */
            /* as well as what was just produced */
            cout << "Belt: " << *(FrgPtr->FrogBeltPtr) << " frogs + " <<
            *(FrgPtr->EscargotBeltPtr) << " escargots = " <<
            *(FrgPtr->FrogBeltPtr) + *(FrgPtr->EscargotBeltPtr) <<
            ". produced: " << *(FrgPtr->ProdValPtr) << "\tAdded " <<
            FrgPtr->Name << ".\n" << flush;

            sem_post(FrgPtr->MutexPtr); /* mutex up */
            sem_post(FrgPtr->UnconsumedPtr); /* candy on belt up */
            /* sleep after to mimic produce time */
            /* milliseconds converted to seconds as sleep() takes in seconds */
            //sleep((FrgPtr->produce_time)/1000);
            Sleep(FrgPtr->produce_time);
            //sleep(10/1000);
            /* delay to disallow even the base case to overproduce candies */
            Sleep(10);
        }
        /* else continue to loop */
        else{
            continue;
        }
    }
}

/* func that increments escargot candy on the belt queue */
void* EscargotProducer(void* voidPtr){
    PRODUCER *EscPtr = (PRODUCER*)(voidPtr);
    while(*(EscPtr->ProdValPtr) < 100){
        /* no particular limit on escargot suckers unlike frog bites */
        if((*(EscPtr->FrogBeltPtr) == 3 && *(EscPtr->EscargotBeltPtr) < 7)||
        (*(EscPtr->FrogBeltPtr) == 2 && *(EscPtr->EscargotBeltPtr) < 8)||
        (*(EscPtr->FrogBeltPtr) == 1 && *(EscPtr->EscargotBeltPtr) < 9)||
        (*(EscPtr->FrogBeltPtr) == 0 && *(EscPtr->EscargotBeltPtr) < 10)){
            sem_wait(EscPtr->AvailablePtr); /* conveyor belt slots down */
            sem_wait(EscPtr->MutexPtr); /* mutex down */

            /* add an escargot to the end of the queue */
            EscPtr->BQPtr->push(ESCARGOT);
            /* update associated escargot data */
            *(EscPtr->ProdValPtr) += 1;
            *(EscPtr->EscargotPtr) += 1;
            *(EscPtr->EscargotBeltPtr) += 1;

            /* output of what's been produced and what's on the belt */
            /* as well as what was just produced */
            cout << "Belt: " << *(EscPtr->FrogBeltPtr) << " frogs + " <<
            *(EscPtr->EscargotBeltPtr) << " escargots = " <<
            *(EscPtr->FrogBeltPtr) + *(EscPtr->EscargotBeltPtr) <<
            ". produced: " << *(EscPtr->ProdValPtr) << "\tAdded " <<
            EscPtr->Name << ".\n" << flush;

            sem_post(EscPtr->MutexPtr); /* mutex up, exit */
            sem_post(EscPtr->UnconsumedPtr); /* unconsumed candy on belt up */
            //sleep((FrgPtr->produce_time)/1000);
            Sleep(EscPtr->produce_time);
            /* delay to disallow the base case to overproduce candies */
            //sleep(10/1000);
            Sleep(10);
        }
        else{
            continue;
        }
    }
}
