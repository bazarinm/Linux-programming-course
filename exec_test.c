#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *env[])
{
	pid_t ch_pid;

	if((ch_pid = fork()) == 0) //child process
	{
		execve(argv[1], argv + 1, env); //execute a program
	} 
	else //parent process
	{
		wait(&ch_pid); //wait for child's return status
	}
}
