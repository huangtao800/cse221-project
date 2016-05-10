#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h>
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
    for (; j < loops; ++j) {
        start = rdtsc();
        send(sockfd, &msg, 1, 0);
        recv(sockfd, &msg, 1, 0);
        end = rdtsc();
		total += (end - start);
    }
    close(sockfd);
    printf ("Round Trip Cycles are : %llu\n", total/loops);
	printf("finished \n");
    
	return 0;
}