#include <queue>
#ifndef BELT_HEADER
#define BELT_HEADER

typedef enum{
    INCREMENT,
    DECREMENT
} OPERATION;

typedef enum{
    FROG=1,
    ESCARGO=2
} CANDY;

class BeltQueue{
    public:
        int fr, tail, max_len;
        int *qu;
        BeltQueue(int len);
        void push(int candy);
        int pop();
};

#endif // BELT_HEADER
