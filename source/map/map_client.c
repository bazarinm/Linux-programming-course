#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAP_SIZE 1024
int main(int argc, char *argv[])
{
	int shm_fd;
	char *pp;
	sem_t *sem;

	shm_fd = shm_open("/shml", O_RDWR, 0755);
	sem = sem_open("/mysem", O_RDWR, 0755, 1);

	pp = (char*) mmap(NULL, MAP_SIZE,\
			  PROT_READ, MAP_SHARED, shm_fd, 0);
	close(shm_fd);
	
	while(1) 
	{
		sem_wait(sem);
		printf("%s\n", pp);
		sem_post(sem);
		getchar();
	}
}
