#include <unistd.h>
#include <windows.h>
#include <semaphore.h>
#include <iostream>
#include "consumer.h"
#include "belt.h"

using namespace std;

void *LucyConsumer(void* voidPtr){
    CONSUMER *dataPtr = (CONSUMER*)(voidPtr);

    while(*(dataPtr->ConsumedValPtr) < 100){

        Sleep(dataPtr->consume_time);

        sem_wait(dataPtr->UnconsumedPtr);
        sem_wait(dataPtr->MutexPtr);

        /* critical section that removes first item */
        *(dataPtr->ConsumedValPtr) += 1;
        if(dataPtr->BQPtr->pop() == FROG){
            *(dataPtr->ConsumedFrogPtr) += 1;
            *(dataPtr->FrogBeltPtr) -= 1;
        }
        else if(dataPtr->BQPtr->pop() == ESCARGOT){
            //*(dataPtr->EscargotBeltPtr) -= 1;
        }

        //cout << "pop: ";
        //dataPtr->BQPtr->printQueue();

        sem_post(dataPtr->MutexPtr);
        sem_post(dataPtr->AvailablePtr);

    }
}
