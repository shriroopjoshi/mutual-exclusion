#include <iostream>
#include <cmath>

#include "tournament.h"

bool tournament :: instance = false;
tournament* tournament :: m = NULL;

tournament :: tournament(int i) {
    // extend the number of processes to the next exponent of 2
    int q = (int) pow(2, (int) ceil(log2(i)));
    // number of nodes in complete tree = number of leaves + (number of leaves - 1)
    n = q + (q - 1);
    // points to first leaf (process)
    p = q - 1;
    z = i;
    // initialize a 2d array.[process * level/process]
    process = new int[i * z];
    flag = new bool[n];
    victim = new int[q - 1];
    for(int j = 0; j < i * z; ++j)
        process[j] = -1;
    for(int j = 0; j < n; ++j)
        flag[j] = false;
}

tournament :: ~tournament() {
    delete[] process;
    delete[] flag;
    delete[] victim;
}

tournament* tournament :: getLock(int n) {
    if(!instance) {
        m = new tournament(n);
        instance = true;
    }
    return m;
}

void tournament :: lock(int pid) {
    int ipid = p + pid - 1;                                             // pid is indexed from 1.
                                                                        // ipid is index of flag[]
    int k = (int) ceil(log2(z));                                        // number oof levels = height(tree)
    for(int i = 0; i < k; ++i) {
        flag[ipid] = true;
        victim[(ipid - 1) / 2] = pid;
        if(ipid % 2 == 0) {
            while(flag[ipid - 1] & (victim[(ipid - 1) / 2] == pid));    // if other process is not requesing CS
        } else {                                                        // move ahead by just checking the flag
            while(flag[ipid + 1] & (victim[(ipid - 1) / 2] == pid));    // otherwise, check victim
        }
        process[(pid - 1) * z + i] = ipid;                              // store the index for unlocking
        ipid = (ipid - 1) / 2;
    }
}

void tournament :: unlock(int pid) {
    int k = (int) ceil(log2(z));                                        // number of levels = height(tree)
    for(int j = 0; j < k; ++j) {
        flag[process[(pid - 1) * z + j]] = false;                       // unlock using stored index
    }

}