#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h>
#include <math.h>
#include "../CPU/helper.h"

int main(int argc , char *argv[])
{      
	
	int loops = 1000;
	int port = 8003;

    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
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

    // Computing round trip time
    char msg = 'a';
    unsigned long long start,end;
	unsigned long long total = 0;
	int j = 0;
    long list[loops];
    for (; j < loops; ++j) {
        start = rdtsc();
        send(sockfd, &msg, 1, 0);
        recv(sockfd, &msg, 1, 0);
        end = rdtsc();
		total += (end - start);
        list[j] = end - start;
    }
    close(sockfd);
    long avg = total / loops;
    printf ("Round Trip Cycles are : %ld\n", avg);
	double ti = avg / 2.5 / (1000000);
    printf ("Time: %f\n", ti);

    double std = 0.0;
    double sum = 0.0;
    for(j=0;j<loops;j++){
        sum += (list[j] - avg) * (list[j] - avg);
    }
    std = sqrt(sum / loops);
    printf ("Std : %f\n", std);

    printf("finished \n");
	return 0;
}