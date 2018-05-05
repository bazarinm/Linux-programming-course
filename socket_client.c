#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sock, ret;
	int client_sock;
	struct sockaddr_in tcp_addr;
	char buf[256];

	sock = socket(AF_INET, SOCK_STREAM, 0);

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*) &ret, sizeof(ret));

	tcp_addr.sin_family = AF_INET;
	tcp_addr.sin_port = htons(5555);
	tcp_addr.sin_addr.s_addr = inet_addr(argv[1]);
	connect(sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr));
	if(ret == -1) perror("bind error");

	while(1)
	{	
		gets(buf);
		ret = send(sock, buf, strnlen(buf, sizeof(buf)), 0);
	}
}

