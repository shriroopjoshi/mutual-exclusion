#include <iostream>
#include <thread>
#include <ctime>
#include <fstream>

#include "bakery.h"

#define CSV_FILE "CS-wait-time.csv"

using namespace std;

void executeCS(bakery*, int);
void critical_section(int, double);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std :: cerr << "USAGE: bakery <n>" << std :: endl;
        std :: exit(1);
    }
    int n = atoi(argv[1]);
    bakery *l;
    std :: thread t[n];
    l = bakery :: getLock(n);
    for(int i = 0; i < n; ++i) {
        t[i] = std :: thread(executeCS, l, i + 1);
    }
    for(auto& th: t)
        th.join();
    return 0;
}

void executeCS(bakery *lock, int i) {
    clock_t start = clock();
    lock -> lock(i);
    clock_t end = clock();
    double t = double(end - start) / (CLOCKS_PER_SEC);
    critical_section(i, t);
    lock -> unlock(i);
}

void critical_section(int pid, double time) {
    cout << "[THREAD-" << pid << "]: Waited for " << time << "secs" << endl;
    ofstream ofs;
    ofs.open(CSV_FILE, ofstream :: out | ofstream :: app);
    ofs << pid << ", " << time << endl;
    ofs.close();
}