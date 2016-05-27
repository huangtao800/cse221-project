#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "../CPU/helper.h"

int main(int argc , char *argv[])
{      
	
	int loops = 10;
	int port = atoi(argv[2]);
    long size = atol(argv[3]);

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

    // Computing round trip time
    char *msg = (char*)malloc(size);
    unsigned long long start,end;
	unsigned long long total = 0;
	int j = 0;
    int n;
    start = rdtsc();
    for (; j < loops; ++j) {
        n = send(sockfd, msg, size, 0);
    }
    end = rdtsc();
    if(n < 0) {
        perror("send failed");
        return -1;
    }
    close(sockfd);
    free(msg);
    total = end - start;
    printf ("PEAK bandwidth is : %f MB/s \n", 10*(size/(1024*1.0*1024)) * (2.5e9 / total) );
    
	return 0;
}