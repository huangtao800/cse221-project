#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include "../CPU/helper.h"

int main(int argc , char *argv[])
{      
	
	int loops = 100;
	int port = 8003;
    // unsigned long long s1, e1;

    // s1 = rdtsc();
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    int sockfd;
    
    
    
    // Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) {
        perror("Error: fails to create socket");
		return -1;
	}

	if (connect(sockfd,(struct sockaddr *)&server,sizeof(server)) < 0) {
		perror("ERROR connecting");
		return -1;
	}
    // e1 = rdtsc();

    // Computing round trip time
    char msg[64];
    unsigned long long start,end;
	unsigned long long total = 0;
	int j = 0;
    double list[loops];
    for (; j < loops; ++j) {
        start = rdtsc();
        send(sockfd, &msg, 64, 0);
        recv(sockfd, &msg, 64, 0);
        end = rdtsc();
		total += (end - start);
        list[j] = (end - start) / 2.5 / 1000000;
    }
    close(sockfd);
    long avg = total / loops;
    printf ("Round Trip Cycles are : %ld\n", avg);
	double ti = avg / 2.5 / (1000000);
    printf ("Time: %f\n", ti);

    double std = 0.0;
    double sum = 0.0;
    for(j=0;j<loops;j++){
        sum += (list[j] - ti) * (list[j] - ti);
    }
    std = sqrt(sum / loops);
    printf ("Std : %f\n", std);

    printf("finished \n");
	return 0;
}