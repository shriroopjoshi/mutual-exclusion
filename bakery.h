#ifndef BAKERY_H_
#define BEKERY_H_

#include "algo.h"

class bakery : public algo {
    static bool instance;
    static bakery *m;
    bool *choosing;
    int *token;
    int n;

    bakery(int i);
    int max(int *);

public:

    static bakery* getLock(int);
    void lock(int) override;
    void unlock(int) override;
    ~bakery();
};

#endif