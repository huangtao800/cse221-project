#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h>


int main(int argc , char *argv[])
{

	int loops = 100;

	int port = 8003;

    int sockfd , newsockfd , client_len;
    struct sockaddr_in serv_addr , cli_addr;
    
    client_len = sizeof(struct sockaddr_in);
    
	//Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd < 0) {
        printf("Error: fails to create socket");
		return -1;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
     
    //Prepare the sockaddr_in structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( port );
     
    //Bind
    if(bind(sockfd,(struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0) {
        perror("Error: fails to bind");
        return 1;
    }
     
    //Listen
    listen(sockfd , 3);
     
    //Accept incoming connection
    puts("Waiting   ...  \n");
    char msg[64];

    //accept connection from an incoming client
    while(1)
    {
    	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&client_len);
    	
		if (newsockfd < 0) {
            perror("Error: fails to accept");
            return -1;
    	}

		int j = 0;
        for (; j < loops; ++j) {
            recv(newsockfd, msg, 64, 0);
            send(newsockfd, msg, 64, 0);
        }
    }

    puts("Finish calculating \n");
     
    return 0;
}