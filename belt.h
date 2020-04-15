#ifndef BELT_HEADER
#define BELT_HEADER

/* used to identify between candies in int queue */
/* and a simple way to collect data */
typedef enum{
    FROG = 1,
    ESCARGOT = 2
} CANDY;

/* since std queue doesn't allow a fixed capacity, a int ptr array was used */
class BeltQueue{
    public:
        BeltQueue(int len); /* constructor takes in fixed length */
        int head; /* front of the queue */
        int tail; /* end of the queue */
        int max_len; /* maximum length of the belt queue */
        int *qu; /* int ptr array that will act like a FIFO queue */
        bool push(int candy); /* add candy to back with bool return value */
        int pop(); /* pop out front candy and return value */
};

#endif // BELT_HEADER
