#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<time.h>
#include<string.h>

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c, n_client;
	struct sockaddr_in server , client;
	char msg[2000], buffer[2000], response[30];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8889 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while
	(new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)){

	recv(new_socket, msg, 2000, 0);
	printf("Client : %s",msg);

	n_client++;
        time_t currentTime;
        time(&currentTime);
        printf("Client %d Sent by %s", n_client, ctime(&currentTime));
        send(new_socket, ctime(&currentTime), 30, 0);

	printf("Server : "); 
	fgets(buffer, 2000, stdin);
	send(new_socket, buffer, 2000, 0);

	recv(new_socket, response, 29, 0);
	printf("received by: %s", response);
	}

	if(new_socket < 0)
		perror("accept()");

	return 0;
}
