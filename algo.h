#ifndef ALGO_H_
#define ALGO_H_

/**
 * base class for both algorithms
 */
class algo {
public:
    /* function for requesting lock */
    virtual void lock(int) = 0;

    /* function for releasing lock */
    virtual void unlock(int) = 0;
};

#endif