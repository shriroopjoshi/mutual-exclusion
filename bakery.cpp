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
    choosing[pid] = true;                       // DOORWAY section
    token[pid] = 1 + max(token);                // set token one greater than max present 
    choosing[pid] = false;

    std :: pair<int, int> ti(token[pid], pid);  // WAITING section
    for(int j = 0; j < n; ++j) {                // create a pair of <token, id>
        while(choosing[j] == true);             // wait till everyone has a token
        std :: pair<int, int> tj(token[j], j);  // compare everyone's pair with seld
        while(token[j] != 0 && tj < ti);        // thread with lowest pair gets the lock
    }
}

void bakery :: unlock(int pid) {
    token[pid] = 0;                             // set the token to minimum
}

int bakery :: max(int token[]) {
    int max = token[0];
    for(int i = 1; i < n; ++i) {
        if(max < token[i])
            max = token[i];
    }
    return max;
}
