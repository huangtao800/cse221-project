#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include "../CPU/helper.h"

int main() 
{
	// struct timespec time1 = {0, 0};
	// struct timespec time2 = {0, 0};
	
	//To generate file "random", execute the command 
	// "dd if=/dev/urandom of=random bs=1048576 count=3072"
	int fileDes = open("random", O_RDWR);
	if (fileDes < 0) {
		printf("Open failed.\n");
		return -1;
	}
	
	unsigned int offset = 1677216; //16 MB
	unsigned int FILESIZE = 3435973836; //2.8 GB
	
	char* map = (char*) mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fileDes, 0);
	
	char c;
	//long total_time = 0;
	uint64_t total_time = 0;
	uint64_t start;
	uint64_t end;

	//clock_gettime(CLOCK_REALTIME, &time1);
	start = rdtsc();
	int i;
	for (i = 0; i < 100; i++) {
		//printf("i= %d\n", i );
		c = map[(((i + 1) * offset) % (FILESIZE - 1))];
	}
	end = rdtsc();
	//clock_gettime(CLOCK_REALTIME, &time2);
	//total_time = time2.tv_nsec - time1.tv_nsec;
	total_time = end - start;

	//printf("start time: %d\n", start );
	//printf("end time: %d\n", end);
	//printf("total_time: %d cycles\n", total_time);

	double averageTime = (double)(total_time - 106) / 100 - 6;
	printf("Average time: %lf\n", averageTime);
	munmap(map, FILESIZE);
	close(fileDes);
	return 0; 
}