#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t ch_pid;
	int sock, ret = 1;
	int client_sock;
	struct sockaddr_in tcp_addr;
	char buf[256];

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
		
		if((ch_pid = fork()) == 0) {//child process
			while(1) {
				ret = recv(client_sock, buf, sizeof(buf), 0);
				if (ret == 0) {
					shutdown(client_sock, SHUT_RDWR);
					exit(0);
				}
				buf[ret] = '\0';
				printf("msg from client: %s\n", buf);
			}
		}

	}
}

