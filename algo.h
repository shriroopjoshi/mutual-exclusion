#ifndef ALGO_H_
#define ALGO_H_

class algo {
public:
    virtual void lock(int) = 0;
    virtual void unlock(int) = 0;
};

#endif