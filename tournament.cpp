#include <iostream>
#include <cmath>

#include "tournament.h"

bool tournament :: instance = false;
tournament* tournament :: m = NULL;

tournament :: tournament(int i) {
    n = i + (i - 1);
    p = i - 1;
    z = i;
    int k = (int) ceil(log2(z));
    process = new int[i * z];
    flag = new bool[n];
    victim = new int[i - 1];
    for(int j = 0; j < k; ++j)
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
    int ipid = p + pid - 1;
    int k = (int) ceil(log2(z));
    for(int i = 0; i < k; ++i) {
        flag[ipid] = true;
        victim[(ipid - 1) / 2] = pid;
        if(ipid % 2 == 0) {
            while(flag[ipid - 1] && victim[(ipid - 1) / 2] == pid);
        } else {
            while(flag[ipid + 1] && victim[(ipid - 1) / 2] == pid);
        }
        process[(pid - 1) * z + i] = ipid;
        ipid = (ipid - 1) / 2;
    }
}

void tournament :: unlock(int pid) {
    int k = (int) ceil(log2(z));
    for(int j = 0; j < k; ++j) {
        flag[process[(pid - 1) * z + j]] = false;
    }

}