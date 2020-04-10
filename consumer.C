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
        /* if queue is not empty we proceed */
        if(dataPtr->BQPtr->head != dataPtr->BQPtr->tail){
            Sleep(dataPtr->consume_time);
            sem_wait(dataPtr->UnconsumedPtr);
            sem_wait(dataPtr->MutexPtr);
            if(dataPtr->BQPtr->pop() == FROG){
                *(dataPtr->ConsumedFrogPtr) += 1;
                *(dataPtr->FrogBeltPtr) -= 1;
                cout << "popped: FROG \n" << flush;
                *(dataPtr->ConsumedValPtr) += 1;
            }
            else{
                *(dataPtr->ConsumedEscargotPtr) += 1;
                *(dataPtr->EscargotBeltPtr) -= 1;
                cout << "popped: ESCARGOT \n" << flush;
                *(dataPtr->ConsumedValPtr) += 1;
            }
            sem_post(dataPtr->MutexPtr);
            sem_post(dataPtr->AvailablePtr);
        }
    }
}

void *EthelConsumer(void* voidPtr){
    CONSUMER *dataPtr = (CONSUMER*)(voidPtr);
    while(*(dataPtr->ConsumedValPtr) < 100){
        if(dataPtr->BQPtr->head != dataPtr->BQPtr->tail){
            Sleep(dataPtr->consume_time);
            sem_wait(dataPtr->UnconsumedPtr);
            sem_wait(dataPtr->MutexPtr);
            if(dataPtr->BQPtr->pop() == FROG){
                *(dataPtr->ConsumedFrogPtr) += 1;
                *(dataPtr->FrogBeltPtr) -= 1;
                cout << "popped: FROG \n" << flush;
                *(dataPtr->ConsumedValPtr) += 1;
            }
            else{
                *(dataPtr->ConsumedEscargotPtr) += 1;
                *(dataPtr->EscargotBeltPtr) -= 1;
                cout << "popped: ESCARGOT \n" << flush;
                *(dataPtr->ConsumedValPtr) += 1;
            }
            sem_post(dataPtr->MutexPtr);
            sem_post(dataPtr->AvailablePtr);
        }
    }
}
