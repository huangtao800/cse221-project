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
#include <functional>   // std::minus
#include <numeric>
#include <math.h>       /* sqrt */
#include "helper.h"

#define TIMES 1000000
#define CREATE_TIMES 500

using namespace std;

double computeStd(vector<uint64_t> &v, double avg){
    double mean = avg;
    
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(),
                   std::bind2nd(std::minus<double>(), mean));
    double sq_sum = inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = sqrt(sq_sum / v.size());
    return stdev;
}

double readOverhead(vector<uint64_t> &v){
    uint64_t start, end;
    double sum = 0;
    for(int i=0; i<TIMES;i++){
        start = rdtsc();
        end = rdtsc();
        sum += end - start;
        v.push_back(end-start);
    }
    double avg = sum / TIMES;
    return avg;
}

double loopOverhead(vector<uint64_t> &v){
    uint64_t start, end;
    double sum = 0;
    for(int i=0;i<10;i++){
        start = rdtsc();
        for(int i=0; i<TIMES; i++){
        }
        end = rdtsc();
        double diff = end - start;
        double avg = diff / TIMES;
        sum += avg;
        v.push_back(avg);
    }
    return sum / 10;
}

void procedureCallOverhead(vector<double> &ret, vector<double> &std){
    uint64_t start, end;
    uint64_t sum = 0;
    vector<uint64_t> v;
    
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func0();
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg1 = sum / TIMES;
    ret.push_back(avg1);
    double std1 = computeStd(v, avg1);
    std.push_back(std1);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func1(1);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg2 = sum / TIMES;
    ret.push_back(avg2);
    double std2 = computeStd(v, avg2);
    std.push_back(std2);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func2(1, 2);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg3 = sum / TIMES;
    ret.push_back(avg3);
    double std3 = computeStd(v, avg3);
    std.push_back(std3);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func3(1, 2, 3);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg4 = sum / TIMES;
    ret.push_back(avg4);
    double std4 = computeStd(v, avg4);
    std.push_back(std4);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func4(1, 2, 3, 4);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg5 = sum / TIMES;
    ret.push_back(avg5);
    double std5 = computeStd(v, avg5);
    std.push_back(std5);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func5(1, 2, 3, 4, 5);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg6 = sum / TIMES;
    ret.push_back(avg6);
    double std6 = computeStd(v, avg6);
    std.push_back(std6);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func6(1, 2, 3, 4, 5, 6);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg7 = sum / TIMES;
    ret.push_back(avg7);
    double std7 = computeStd(v, avg7);
    std.push_back(std7);
    
    sum = 0;
    v.clear();
    for(int i=0;i<TIMES;i++){
        start = rdtsc();
        func7(1, 2, 3, 4, 5, 6, 7);
        end = rdtsc();
        sum += (end - start);
        v.push_back(end-start);
    }
    double avg8 = sum / TIMES;
    ret.push_back(avg8);
    double std8 = computeStd(v, avg8);
    std.push_back(std8);
}

double systemCallOverhead(vector<uint64_t> &v){
    uint64_t start, end;
    uint64_t sum = 0;
    for(int i=0;i<TIMES;i++){
        rdtsc();
        start = rdtsc();
        getpid();
        end = rdtsc();
        sum += end - start;
        if(i==0)    cout << "1st iteration: " << end - start << endl;
        v.push_back(end - start);
    }
    double avg = (double)sum / (double)TIMES;
    return avg;
}

void* newThread(void *){
    pthread_exit(NULL);
}

double newThreadOverhead(vector<uint64_t> &v){
    pthread_t t;
    uint64_t start, end;
    uint64_t sum = 0;
    for(int i=0;i<CREATE_TIMES;i++){
        start = rdtsc();
        pthread_create(&t, NULL, newThread, NULL);
        end = rdtsc();
        sum += end - start;
        pthread_join(t, NULL);
        v.push_back(end-start);
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}

// Compute overhead of creating a new process
double newProcessOverhead(vector<uint64_t> &v){
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
            v.push_back(end-start);
        }
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}


double processSwitch(vector<uint64_t> &v){
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
            v.push_back(end-start);
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

double threadSwitch(vector<uint64_t> &v){
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
        v.push_back(end-start);
    }
    double avg = sum / CREATE_TIMES;
    return avg;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    vector<uint64_t> v;
    double t1 = readOverhead(v);
    cout << "read overhead: " << t1 << endl;
    double std1 = computeStd(v, t1);
    cout << "read std: " << std1 << endl;

    v.clear();
    double t2 = loopOverhead(v);
    cout << "loop overhead: " << t2 << endl;
    double std2 = computeStd(v, t2);
    cout << "loop std: " << std2 << endl;

//    vector<double> times;
//    vector<double> std;
//    procedureCallOverhead(times, std);
//    for(int i=0;i<times.size();i++){
//        cout << "procedure call of " << i << " arguments overhead: " << times[i] << endl;
//        cout << "procedure call of " << i << " arguments std: " << std[i] << endl;
//    }
    
//    v.clear();
//    double t4 = systemCallOverhead(v);
//    double std4 = computeStd(v, t4);
//    cout << "system call overhead: " << t4 << endl;
//    cout << "system call std: " << std4 << endl;
//    
//   
//    
//    v.clear();
//    double t5 = newThreadOverhead(v);
//    cout << "new thread overhead: "<< t5 << endl;
//    double std5 = computeStd(v, t5);
//    cout << "new thread std: " << std5 << endl;
//
//    v.clear();
//    double t6 = newProcessOverhead(v);
//    cout << "new process overhead: " << t6 << endl;
//    double std6 = computeStd(v, t6);
//    cout << "new process std: " << std6 << endl;
//
    v.clear();
    double t7 = processSwitch(v);
    cout << "process context switch overhead: " << t7 << endl;
    double std7 = computeStd(v, t7);
    cout << "process context switch std: " << std7 << endl;
    
//    v.clear();
//    double t8 = threadSwitch(v);
//    cout << "thread context switch overhead: " << t8 << endl;
//    double std8 = computeStd(v, t8);
//    cout << "thread context switch std: " << std8 << endl;
    return 0;
}
