#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* new_connection(void* client_sock);

int main()
{
	pid_t ch_pid;
	pthread_t thread;
	int sock, ret = 1;
	int client_sock;
	struct sockaddr_in tcp_addr;


	sock = socket(AF_INET, SOCK_STREAM, 0);

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*) &ret, sizeof(ret));

	tcp_addr.sin_family = AF_INET;
	tcp_addr.sin_port = htons(5555);
	tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr));
	if(ret == -1) perror("bind error");

	listen(sock, 5);

	while(1)
	{
		client_sock = accept(sock, NULL, 0);
		
		pthread_create(&thread, NULL, &new_connection, (void*) &client_sock);
	}
}

void* new_connection(void* cli_s) 
{
	int ret;
	int client_sock = * ((int*) cli_s);
	char buf[256];
	while(1) {
		ret = recv(client_sock, buf, sizeof(buf), 0);
		if (ret == 0) {
			shutdown(client_sock, SHUT_RDWR);
			break;
		}
		buf[ret] = '\0';
		printf("msg from client: %s\n", buf);
	}
}


