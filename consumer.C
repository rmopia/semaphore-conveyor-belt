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

        sem_wait(dataPtr->MutexPtr);
        /* critical section that removes first item */

        sem_post(dataPtr->MutexPtr);

    }
}
