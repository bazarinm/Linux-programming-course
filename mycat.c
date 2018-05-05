#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, count = 1;
	char buf[128];
	fd = open(argv[1], O_RDONLY);
	while(count > 0) 
	{
		count = read(fd, buf, sizeof(buf));
		write(1, buf, count);
	}
	close(fd);
	return 0;
}
