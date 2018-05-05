#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int loc_fd, dest_fd, count = 1;	
	char buf[128];
	struct stat stats;

	loc_fd = open(argv[1], O_RDONLY);
	fstat(loc_fd, &stats);

	dest_fd = creat(argv[2], O_RDWR);
	while(count > 0) 
	{
		count = read(loc_fd, buf, sizeof(buf));
		write(dest_fd, buf, count);
	}

	fchmod(dest_fd, stats.st_mode);
	close(loc_fd);
	close(dest_fd);
}

