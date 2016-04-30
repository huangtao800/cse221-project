#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../CPU/helper.h"
#define LOOP 10


void readBandwidth(){
	uint64_t start, end, sum;
	long long size = 64 * 1024 * 1024; // 64 MB

	double total_bandwidth = 0;
	int x = 0;
	for(;x<LOOP;x++){
		long *arr = (long *)malloc(size);
		memset(arr, '0', size);
		long long arrsize = size / sizeof(long);

		int i = 0;

		start = rdtsc();
		for(;i<arrsize;i+=8){
			long t = arr[i];
		}
		end = rdtsc();
		sum = end - start;

		free(arr);
		double bandwidth = (size * 1.0 / pow(2, 20) / sum) * 2.5 * pow(2, 30); // MB/s
		total_bandwidth += bandwidth;
	}

	double avg = total_bandwidth / LOOP;
	
	printf ("RAM read bandwidth: %f MB/s\n", avg);
}

void writeBandwidth(){
	uint64_t start, end, sum;
	long long size = 64 * 1024 * 1024; // 64 MB

	double total_bandwidth = 0;
	int x = 0;
	for(;x<LOOP;x++){
		long *arr = (long *)malloc(size);
		memset(arr, '0', size);
		long long arrsize = size / sizeof(long);

		int i = 0;

		start = rdtsc();
		for(;i<arrsize;i+=8){
			arr[i] = 1;
		}
		end = rdtsc();
		sum = end - start;

		free(arr);
		double bandwidth = (size * 1.0 / sum) * 2.5 * pow(2, 10); // MB/s
		total_bandwidth += bandwidth;
	}

	double avg = total_bandwidth / LOOP;
	
	printf ("RAM write bandwidth: %f MB/s\n", avg);
}

int main(){
	readBandwidth();
	writeBandwidth();
}