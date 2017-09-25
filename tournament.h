#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include "algo.h"

/**
 * tournament class is implementation of Peterson's tournament algorithm for mutual exclusion.
 * It's base class is algo which is a virtual class containing lock() and unlock()
 */
class tournament : public algo {
    /* variables for singleton pattern */
    static bool instance;
    static tournament *m;
    
    /* number of nodes in the tree */
    int n;
    
    /* points to first node containing process */
    int p;
    
    /* number of processes */
    int z;
    
    /* Used to store index of flag array. Used while unlocking */
    volatile int *process;
    
    /* Flags for requesting CS
       size(flag) = n + (n - 1) where n = number of processes */
    volatile bool *flag;
    
    /* Stores victim for each pair of process on each level
       size(victim) = (n - 1) */
    volatile int *victim;

    /* initializes memory for z processes */
    tournament(int);

public:

    /* gives same object. If object is not present, it creates one */
    static tournament* getLock(int);

    /* Requests a lock for CS
       pid: the process-id (thread-id) of requesting process */
    void lock(int pid) override;

    /* Releases previously acquired lock
       pid: the process-id (thread-id) of the process */
    void unlock(int pid) override;

    /* frees memory initialized for z processes */
    ~tournament();
};

#endif
