#include <iostream>

#include "bakery.h"

bool bakery :: instance = false;
bakery* bakery :: m = NULL;

bakery :: bakery(int i) {
        n = i;
        choosing = new bool[n];
        token = new int[n];
        for(int i = 0; i < n; i++)
            choosing[i] = false;
        for(int i = 0; i < n; i++)
            token[i] = 0;
    }

bakery :: ~bakery() {
    delete[] choosing;
    delete[] token;
    instance = false;
}

bakery* bakery :: getLock(int n) {
    if(!instance) {
        m = new bakery(n);
        instance = true;
    }
    return m;
}

void bakery :: lock(int pid) {
    // doorway
    choosing[pid] = true;
    token[pid] = 1 + max(token);
    choosing[pid] = false;

    // waiting
    std :: pair<int, int> ti(token[pid], pid);
    for(int j = 0; j < n; ++j) {
        while(choosing[j] == true);
        std :: pair<int, int> tj(token[j], j);
        while(token[j] != 0 && tj < ti);
    }
}

void bakery :: unlock(int pid) {
    token[pid] = 0;
}

int bakery :: max(int token[]) {
    int max = token[0];
    for(int i = 1; i < n; ++i) {
        if(max < token[i])
            max = token[i];
    }
    return max;
}
