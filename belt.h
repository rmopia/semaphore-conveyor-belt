#include <queue>
#ifndef BELT_HEADER
#define BELT_HEADER

typedef enum{
    FROG=1,
    ESCARGOT=2
} CANDY;

class BeltQueue{
    public:
        int head, tail, max_len;
        int *qu;
        BeltQueue(int len);
        void push(int candy);
        int pop();
        void printQueue();
};

#endif // BELT_HEADER
