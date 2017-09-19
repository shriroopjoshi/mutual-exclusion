#include <iostream>
#include <thread>

#include "bakery.h"

bool bakery :: instance = false;
bakery* bakery :: m = NULL;

bakery :: bakery(int i) {
        n = i;
        choosing = new bool[n];
        token = new int[n];
        for(int i = 0; i < n + 1; i++)
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
    pid -= 1;
    choosing[pid] = true;                               // DOORWAY section
    token[pid] = 1 + max(token);                        // set token one greater than max present 
    choosing[pid] = false;

    for(int j = 0; j < n; ++j) {                        // WAITING section
        if(j != pid) {
            while(choosing[j] == true)                  // wait till everyone has a token
                std :: this_thread :: yield();
            while((token[j] != 0) &&                    // compare everyone's pair with seld
                                                        // thread with lowest pair gets the lock
            (token[pid] > token[j] || (token[pid] == token[j] && pid > j)))
                std :: this_thread :: yield();
        }
    }
}

void bakery :: unlock(int pid) {
    pid -= 1;
    token[pid] = 0;                                     // set the token to minimum
}

int bakery :: max(int token[]) {
    int max = token[0];
    for(int i = 1; i < n; ++i) {
        max = std :: max(token[i], max);
    }
    return max;
}
