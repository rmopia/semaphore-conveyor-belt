#include <iostream>
#include "belt.h"

BeltQueue::BeltQueue(int len){
    this->head = 0;
    this->tail = 0;
    this->max_len = len;
    this->qu = new int[max_len];
    for(int i = 0; i < max_len; i++){
        this->qu[i] = 0;
    }
}

void BeltQueue::push(CANDY candy){
    if(this->max_len != this->tail){
        this->qu[this->tail] = candy;
        this->tail++;
    }
}

int BeltQueue::pop(){
    int candy = 0;
    candy = this->qu[this->head];

    if(this->head != this->tail){
        for(int i = 0; i < this->tail-1; i++){
            this->qu[i] = this->qu[i + 1];
        }
        this->tail--;
        for(int i = tail; i < this->max_len; i++){
            this->qu[i] = 0;
        }
    }

    return candy;
}

void BeltQueue::printQueue(){
    for(int i = 0; i < this->max_len; i++){
        std::cout << this->qu[i] << " ";
    }
    std::cout << std::endl;
}
