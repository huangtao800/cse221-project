#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "../CPU/helper.h"

#define COUNT 1000000
#define TIMES 1000
#define NANOS_PER_SECF 1000000000.0

//Size of memory region that we will accessed, ranging from 4KB to 512MB
int sizeList[18] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288};

int strideList[9] = {4, 16, 64, 128, 1024, 2048, 1048576, 2097152, 4194304};
                //   4B, 16B, 64B, 128B, 1KB, 2KB, 1MB, 2MB, 4MB

double cacheAccessTime(int size, int strideLength);
void fixedStride(int strideIndex, FILE *file, int times);

int main(int argc, const char * argv[])
{

    for(int i=0;i<9;i++){
        for(int j=0;j<18;j++){
            cacheAccessTime(sizeList[j], strideList[i]);
        }
    }
    return 0;
}


double cacheAccessTime(int size, int strideLength)
{
    int* A;
    unsigned long long memsize = (long long)size * 1024;
    A = (int *)malloc(memsize);
    unsigned long long arrsize = memsize / sizeof(int);
    int num, length;
    length = strideLength / sizeof(int);   
    num = size * 1024 / sizeof(int);
    int index;
    A[0] = 0;
    for (int i = 0; i < arrsize; i++) {
        index = i + length;
        if (index >= arrsize) {
            index %= arrsize;
        }
        A[i] = index;
    }

    int x = 0;
    uint64_t start;
    uint64_t end;
    uint64_t total_time = 0;
    int count = COUNT;

    start = rdtsc();
    for (int i = 0; i < count; i++) {
        x = A[x];
    }
    end = rdtsc();
    total_time = end - start - 42;
    double ans = total_time / count - 6;
    free(A);
    printf("Memsize: %llu, Stride: %d bytes, time: %f \n", memsize, strideLength, ans);
    return ans;
}
