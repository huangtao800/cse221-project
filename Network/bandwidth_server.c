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

	int port = 8003;
    long size = atol(argv[1]);

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
    puts("Waiting   ...  \n");

    char *msg=(char*)malloc(size+1);
    memset (msg, 80, size+1);

    //accept connection from an incoming client
    while(1)
    {
    	client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&client_len);
    	
		if (client_sock < 0) {
            perror("Error: fails to accept");
            return -1;
    	}
        unsigned long long start,end,diff;
        int i = 0;
        int n = 0;
        start = rdtsc();
        
        for(;i < 10;i++) {
            n = recv(client_sock, msg, size, MSG_WAITALL);
        }
        
        end = rdtsc();
        printf ("receive : %d\n", n);
        diff = end - start;
        
        printf ("PEAK bandwidth is : %f MB/s \n", 10*(size/(1024*1.0*1024)) * (2.5e9 / diff) );
        
        close(client_sock);
        return 0;
    }
    
    close(server_sock);
    free(msg);
    puts("Finish calculating \n");
     
    return 0;
}