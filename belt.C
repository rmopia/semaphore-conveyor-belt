#include <iostream>
#include "belt.h"

/* constructor for conveyor belt queue */
BeltQueue::BeltQueue(int len){
    this->max_len = len; /* max capacity on the belt */
    this->head = 0; /* head value never changes */
    this->tail = 0; /* tail value changes based on candies on belt */
    this->qu = new int[max_len]; /* capacity of belt is initialized to arr */
    /* fills queue with zeros */
    for(int i = 0; i < max_len; i++){
        this->qu[i] = 0;
    }
}

/* adds a candy at the end of the belt */
bool BeltQueue::push(int candy){
    /* if the queue is not full, add a candy at tail */
    if(this->tail != this->max_len){
        this->qu[this->tail] = candy;
        this->tail += 1; /* iterate to next candy slot */
        return true;
    }
    /* queue is full, return false */
    else{
        return false;
    }
}

/* pops out the element in front of the conveyor belt */
int BeltQueue::pop(){
    int candy = 0;
    /* save popped candy value */
    candy = this->qu[this->head];

    if(this->tail != this->head){
        /* shifts each candy one closer to the front */
        /* while removing the first candy */
        for(int i = 0; i < this->tail - 1; i++){
            this->qu[i] = this->qu[i + 1];
        }
        this->tail -= 1;
        /* fills any removed space with a 0 to prevent junk values */
        for(int i = tail; i < this->max_len; i++){
            this->qu[i] = 0;
        }
    }
    return candy;
}
