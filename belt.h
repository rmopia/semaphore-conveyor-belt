#ifndef BELT_HEADER
#define BELT_HEADER

/* used to identify between candies in int queue and data collection */
typedef enum{
    FROG = 1,
    ESCARGOT = 2
} CANDY;

class Candy{
    public:
        Candy(char* name);
        char* candy_name;
        int candy_num;
};

/* since std queue doesn't allow a fixed capacity, an array was used */
class BeltQueue{
    public:
        BeltQueue(int len); /* constructor takes in fixed length */
        int head, tail, max_len; /* queue details */
        int *qu; /* int array that will act like a FIFO queue */
        bool push(int candy); /* add candy to back with bool return value */
        int pop(); /* pop out front candy and return value */
        void printQueue(); /* used to visualize int array queue */
};

#endif // BELT_HEADER
