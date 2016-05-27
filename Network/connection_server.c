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

int main(){
	int port = 8003;

    int server_sock , client_sock , client_len;
    struct sockaddr_in server , client;
    
    client_len = sizeof(client);
    
	//Create socket
    server_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sock == -1) {
        printf("Error: fails to create socket");
		return -1;
	}
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );

    //Bind
    if(bind(server_sock,(struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("Error: fails to bind");
        return 1;
    }
     
    //Listen
    listen(server_sock , 3);
     
    //Accept incoming connection
    printf("Waiting   ...  \n");

    while(1)
    {
    	client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&client_len);
    	
		if (client_sock < 0) {
            perror("Error: fails to accept");
            return -1;
    	}

		unsigned long long start, end, diff;

		start = rdtsc();
        
        close(client_sock);

		end = rdtsc();

		diff = end - start;

        double ti = diff / 2.5 / (1000000);

		printf("connection shutdwon cycle : %llu \n", diff);
        printf("Tear down time: %f\n", ti);
    }
    
    close(server_sock);

    puts("Finish calculating \n");
     
    return 0;
}