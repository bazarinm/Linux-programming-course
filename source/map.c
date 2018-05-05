#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>

#define MAP_SIZE 1024
int main(int argc, char *argv[])
{
	int shm_fd;
	char *pp;
	sem_t *sem;
	char buf[128];

	shm_fd = shm_open("/shml", O_CREAT|O_RDWR, 0755);
	sem = sem_open("/mysem", O_CREAT|O_RDWR, 0755, 1);
	
	ftruncate(shm_fd, MAP_SIZE);

	pp = (char*) mmap(NULL, MAP_SIZE,\
			  PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	close(shm_fd);

	while(1)
	{
		gets(buf);
		sem_wait(sem);
		sprintf(pp, "%s", buf);
		sem_post(sem);
	}
}
