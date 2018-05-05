#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() 
{
	int fd;
	fd = open("newfile", O_RDWR|O_CREAT, 0755);
	close(1);
	dup2(fd, 1);
	printf("hello\n");
	write(1, "hello2\n", 6);
	getchar();
	close(fd);
}

