#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<time.h>

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c, n_client;
	struct sockaddr_in server , client;
	char msg[2000], buffer[2000];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
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
//	if (new_socket<0)
//		{
//		perror("accept failed");
//		}	
//	puts("Connection accepted");
//	send(new_socket, msg, 2000, 0);
//	recv(new_socket, buffer, 2000, 0);
//	printf("message from client: %s\n", buffer);
	recv(new_socket, buffer, 2000, 0);
	printf("Client : %s\n",buffer);

	printf("Server : "); 
	fgets(buffer, 2000, stdin);
	send(new_socket, buffer, 2000, 0);
//
	n_client++;
	time_t currentTime;
	time(&currentTime);
	printf("Client %d requested for time at %s", n_client, ctime(&currentTime));
	send(new_socket, ctime(&currentTime), 30, 0);
	}

	if(new_socket < 0)
		perror("accept()");

	return 0;
}
