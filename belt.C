#include "belt.h"

BeltQueue::BeltQueue(int len){
    this->fr = 0;
    this->tail = 0;
    this->max_len = len;
    this->qu = new int;
}

void BeltQueue::push(int candy){
    if(this->max_len != this->tail){
        this->qu[this->tail] = candy;
        this->tail++;
    }
}

int BeltQueue::pop(){
    int candy = 0;
    candy = this->qu[this->fr];

    if(this->fr != this->tail){
        for(int i = 0; i < this->tail - 1; i++){
            this->qu[i] = this->qu[i + 1];
        }
        this->tail--;
    }
    return candy;
}
