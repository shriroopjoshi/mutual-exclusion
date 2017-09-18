#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include "algo.h"

class tournament : public algo {
    static bool instance;
    static tournament *m;
    int n, p, z;
    int *process;
    bool *flag;
    int *victim;
    tournament(int i);

public:

    static tournament* getLock(int);
    void lock(int) override;
    void unlock(int) override;
    ~tournament();
};

#endif
