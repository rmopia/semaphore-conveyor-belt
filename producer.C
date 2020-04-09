#include <unistd.h>
#include <windows.h>
#include <semaphore.h>
#include <iostream>
#include "producer.h"
#include "belt.h"

using namespace std;

void* FrogProducer(void* voidPtr){
    PRODUCER *dataPtr = (PRODUCER*)(voidPtr);
    while(*(dataPtr->ProdValPtr) < 100){

        // change sleep timer when we move code //
        Sleep(dataPtr->produce_time); // 1000ms = 1s

        /* sleep to milliseconds (useconds converted) */

        sem_wait(dataPtr->AvailablePtr);
        sem_wait(dataPtr->MutexPtr); /* mutex down */

        /* total production value */
        cout << "here is: " << *(dataPtr->FrogPtr) << "\n" << flush;
        dataPtr->BQPtr->push(FROG);
        *(dataPtr->ProdValPtr)+=1;
        *(dataPtr->FrogPtr)+=1;
        *(dataPtr->FrogBeltPtr)+=1;
        //cout << "push: ";
        //dataPtr->BQPtr->printQueue();

        cout << "Belt: " << *(dataPtr->FrogBeltPtr) << " frogs + " << "0 escargots = " <<
        *(dataPtr->FrogBeltPtr) + 0 << ". produced: " << *(dataPtr->ProdValPtr) << "\tAdded " << dataPtr->Name << endl;

        sem_post(dataPtr->MutexPtr); /* mutex up */
        sem_post(dataPtr->UnconsumedPtr);
    }
}

void* EscargotProducer(void* voidPtr){
    PRODUCER *dataPtr = (PRODUCER*)(voidPtr);
    while(*(dataPtr->ProdValPtr) < 100){

    }
}
