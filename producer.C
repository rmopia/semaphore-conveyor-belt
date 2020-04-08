#include <stdio.h>
#include <semaphore.h>
#include <iostream>
#include "producer.h"
#include "belt.h"

using namespace std;

void* FrogProducer(void* voidPtr){
    int p = 1;
    PRODUCER *dataPtr = (PRODUCER *)(voidPtr);

    cout << "Hello" << "\n" << flush;

    while(*(dataPtr->ProdValPtr) < 100){
        // if else sleep counter here
        cout << *(dataPtr->ProdValPtr) << "\n" << flush;
        *(dataPtr->ProdValPtr)+=1;
    }

}
