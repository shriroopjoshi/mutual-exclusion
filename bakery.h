#ifndef BAKERY_H_
#define BEKERY_H_

#include "algo.h"

/**
 * bakery class is implementation of Lamport's bakery algorithm for mutual exclusion.
 * It's base class is algo which is a virtual class containing lock() and unlock()
 */
class bakery : public algo {
    /* variables for singleton pattern */
    static bool instance;
    static bakery *m;

    /* array for doorway section */
    bool *choosing;

    /* stores token */
    int *token;

    /* number of processes */
    int n;

    /* initializes memory for n processes */
    bakery(int i);

    /* returns maximum value from already present tokens */
    int max(int *token);

public:

    /* gives same object. If object is not present, it creates one */
    static bakery* getLock(int);

    /* Requests a lock for CS
       pid: the process-id (thread-id) of requesting process */
    void lock(int) override;

    /* Releases previously acquired lock
       pid: the process-id (thread-id) of the process */
    void unlock(int) override;

    /* frees memory initialized for n processes */
    ~bakery();
};

#endif