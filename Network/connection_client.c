#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../CPU/helper.h"

int main(int argc , char *argv[]){
	int loops = 50;
	int port = 8003;
    // unsigned long long s1, e1;

    // s1 = rdtsc();
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    int sockfd;

    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) {
        perror("Error: fails to create socket");
		return -1;
	}

	unsigned long long start, end;
	unsigned long long total = 0;

	start = rdtsc();
	if (connect(sockfd,(struct sockaddr *)&server,sizeof(server)) < 0) {
		perror("ERROR connecting");
		return -1;
	}
	end = rdtsc();
	total += end - start;
	
	printf("Cycles: %llu\n", total);
	double ti = total / 2.5 / (1000000);
	printf("Time: %f \n", ti);

	start = rdtsc();
	close(sockfd);
	end = rdtsc();
	total = end - start;
	printf("Close cycles: %llu\n", total);
}