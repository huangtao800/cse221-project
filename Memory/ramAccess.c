#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "../CPU/helper.h"

#define LOOP 1000000

int main(){
	uint64_t start, end, sum;
	srand(time(NULL));

	int size = 5;

	for(;size<28;size++){
		unsigned long long memsize = 1 << size;
		int * arr;
		arr = (int *)malloc(memsize);
		unsigned long long arrSize = memsize / sizeof(int);
		memset(arr, 0, arrSize);

		int i = 0;
		start = rdtsc();
		for(;i<LOOP;i++){
			int pos = rand() % arrSize;
			int temp = arr[pos];
		}
		end = rdtsc();
		sum = end - start;
		double avg = (sum*1.0) / LOOP;
		free(arr);
		printf("Array size %llu: average access cycles = %f \n", memsize, avg);
	}
	return 0;
}

