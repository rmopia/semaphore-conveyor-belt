#include <iostream>
#include "belt.h"

Candy::Candy(char *name){
    this->candy_name = name;
    if(this->candy_name == "Frog"){
        this->candy_num = FROG;
    }
    else{
        this->candy_num = ESCARGOT;
    }
}
/* constructor for conveyor belt */
BeltQueue::BeltQueue(int len){
    this->max_len = len; /* capacity on the belt */
    this->head = 0; /* head value never changes */
    this->tail = 0; /* tail value changes based on space on belt */
    this->qu = new int[max_len]; /* capacity of belt is initialized to arr */
    /* fills queue with zeros */
    for(int i = 0; i < max_len; i++){
        this->qu[i] = 0;
    }
}

bool BeltQueue::push(int candy){
    /* if the queue is not full, add a candy at tail */
    if(this->max_len != this->tail){
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
    int candy;
    /* save popped candy value */
    candy = this->qu[this->head];

    if(this->head != this->tail){
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

/* used for debugging output */
void BeltQueue::printQueue(){
    for(int i = 0; i < this->max_len; i++){
        std::cout << this->qu[i] << " ";
    }
    std::cout << std::endl;
}
