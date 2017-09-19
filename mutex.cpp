#include <iostream>
#include <thread>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <mutex>

#include "bakery.h"
#include "tournament.h"

#define CSV_FILE "CS-wait-time.csv"

void bakery_algorithm(int, const char*);
void tournament_algorithm(int, const char*);
void executeCS(algo*, int, int, const char*);
void critical_section(int, double);
void write_to_file(algo*, int, double, double, const char*);

std :: mutex file_mutex;
int ne = 0;

int main(int argc, char *argv[]) {
    if(argc != 3 && argc != 4) {
        std :: cerr << "USAGE: bakery <bakery|tournament> <n>" << std :: endl;
        std :: exit(1);
    }
    const char *filename;
    if(argc == 4)
        filename = argv[3];
    else
        filename = CSV_FILE;
    int n = atoi(argv[2]);
    if(!strcmp(argv[1], "bakery")) {
        bakery_algorithm(n, filename);
    } else if(!strcmp(argv[1], "tournament")) {
        tournament_algorithm(n, filename);
    } else {
        std :: cerr << "USAGE: bakery <bakery|tournament> <n>" << std :: endl;
        std :: exit(1);
    }
    if(ne == n)
        std :: cout << "MUTUAL EXCLUSION - SUCCESS!" << std :: endl;
    else
        std :: cout << "MUTUAL EXCLUSION - SUCCESS!" << std :: endl;
    return 0;
}

void tournament_algorithm(int n, const char *filename) {
    tournament *l;
    std :: thread t[n];
    srand((unsigned) time(0));
    l = tournament :: getLock(n);
    for(int i = 0; i < n; ++i) {
        int time = 1 + (rand() % 5);
        t[i] = std :: thread(executeCS, l, i + 1, time, filename);
    }
    for(auto& th: t)
        th.join();
}

void bakery_algorithm(int n, const char *filename) {
    bakery *l;
    std :: thread t[n];
    srand((unsigned) time(0));
    l = bakery :: getLock(n);
    for(int i = 0; i < n; ++i) {
        int time = 1 + (rand() % 5);
        t[i] = std :: thread(executeCS, l, i + 1, time, filename);
    }
    for(auto& th: t)
        th.join();
}

void executeCS(algo *lock, int i, int wtime, const char *filename) {
    //std :: this_thread :: sleep_for(std :: chrono :: seconds(wtime));
    clock_t start = clock();
    lock -> lock(i);
    clock_t end = clock();
    double tl = double(end - start) / (CLOCKS_PER_SEC);
    critical_section(i, tl);
    start = clock();
    lock -> unlock(i);
    end = clock();
    double tu = double(end - start) / (CLOCKS_PER_SEC);
    write_to_file(lock, i, tl, tu, filename);
}

void critical_section(int pid, double wtime) {
    std :: cout << "[THREAD-" << pid << "]: Executing critical section"<< std :: endl;
    ne += 1;
    uint count = 0;
    while(count < 65534)
        count += 1;
}

void write_to_file(algo *l, int pid, double tl, double tu, const char *filename) {
    std :: lock_guard<std :: mutex> lock(file_mutex);
    //l -> lock(pid);
    std :: ofstream ofs;
    ofs.open(filename, std :: ofstream :: out | std:: ofstream :: app);
    ofs << pid << ", " << tl << ", " << tu << std :: endl;
    ofs.close();
    //l -> unlock(pid);
}