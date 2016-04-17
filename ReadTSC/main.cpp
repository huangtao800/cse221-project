//
//  main.cpp
//  ReadTSC
//
//  Created by Tao Huang on 4/15/16.
//  Copyright © 2016 Tao Huang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "helper.h"

#define TIMES 1000000
#define CREATE_TIMES 500

using namespace std;

double readOverhead(){
    uint64_t start, end;
    double sum = 0;
    for(int i=0; i<TIMES;i++){
        start = rdtsc();
        end = rdtsc();
        sum += end - start;
    }
    double avg = sum / TIMES;
    return avg;
}

double loopOverhead(){
    uint64_t start, end;
    start = rdtsc();
    for(int i=0; i<TIMES; i++){
    }
    end = rdtsc();
    double diff = end - start;
    double avg = diff / TIMES;
    return avg;
}

void procedureCallOverhead(vector<double> &ret){
    uint64_t start, end;
    uint64_t sum = 0;
    
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func0();
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
    
    sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func1(1);
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
    
    sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func2(1, 2);
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
    
    sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func3(1, 2, 3);
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
    
    sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func4(1, 2, 3, 4);
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
    
    sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func5(1, 2, 3, 4, 5);
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
    
    sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func6(1, 2, 3, 4, 5, 6);
        end = rdtsc();
        sum += (end - start);
    }
    ret.push_back(sum / TIMES);
}

double systemCallOverhead(){
    uint64_t start, end;
    double sum = 0;
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        getpid();
        end = rdtsc();
        sum += end - start;
    }
    double avg = sum / TIMES;
    return avg;
}

void* newThread(void *){
    pthread_exit(NULL);
}

double newThreadOverhead(){
    pthread_t t;
    uint64_t start, end;
    uint64_t sum = 0;
    for(int i=0;i<CREATE_TIMES;i++){
        start = rdtsc();
        pthread_create(&t, NULL, newThread, NULL);
        end = rdtsc();
        sum += end - start;
        pthread_join(t, NULL);
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}

// Compute overhead of creating a new process
double newProcessOverhead(){
    uint64_t start, end;
    uint64_t sum = 0;
    pid_t pid;
    for(int i=0;i<CREATE_TIMES;i++){
        start = rdtsc();
        pid = fork();
        
        if(pid < 0){
            cout << "Create child process failed" << endl;
        }else if(pid == 0){
            exit(1);
        }else{
            end = rdtsc();
            wait(NULL);
            sum += end - start;
        }
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}


double processSwitch(){
    uint64_t start, end;
    uint64_t sum = 0;
    int pipefd[2];
    pid_t pid;
    
    for(int i=0;i<CREATE_TIMES;i++){
        pipe(pipefd);
        pid = fork();
        if(pid < 0){
            cout << "Create child process failed" << endl;
            exit(-1);
        }else if(pid == 0){
            end = rdtsc();
            write(pipefd[1], (void *)&end, sizeof(uint64_t));
            exit(0);
        }else{
            start = rdtsc();
            read(pipefd[1], (void *)&start, sizeof(uint64_t));
            sum += end - start;
            wait(NULL);
        }
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}

static int fd[2];

static inline void *foo(void *) {
    uint64_t t = rdtsc();
    
    write(fd[1], (void*)&t, sizeof(uint64_t));
    
    pthread_exit(NULL);
}

double threadSwitch(){
    uint64_t start, end;
    uint64_t sum = 0;
    
    for(int i=0;i<CREATE_TIMES;i++){
        pipe(fd);
        pthread_t thread;
        pthread_create(&thread, NULL, foo, NULL);
        start = rdtsc();
        read(fd[0], (void *)&end, sizeof(uint64_t));
        pthread_join(thread, NULL);
        sum += end - start;
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    double t1 = readOverhead();
    cout << "read overhead: " << t1 << endl;
    
    double t2 = loopOverhead();
    cout << "loop overhead: " << t2 << endl;
    
    vector<double> times;
    procedureCallOverhead(times);
    for(int i=0;i<times.size();i++){
        cout << "procedure call of " << i << " arguments overhead: " << times[i] << endl;
    }
    
    double t4 = systemCallOverhead();
    cout << "system call overhead: " << t4 << endl;

    double t5 = newThreadOverhead();
    cout << "new thread overhead: "<< t5 << endl;
    
    double t6 = newProcessOverhead();
    cout << "new process overhead: " << t6 << endl;
    
    double t7 = processSwitch();
    cout << "process context switch overhead: " << t7 << endl;
    
    double t8 = threadSwitch();
    cout << "thread context switch overhead: " << t8 << endl;
}
