#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *env[])
{
	pid_t ch_pid;
	if((ch_pid = fork()) == 0) //child process
	{
		char *exec_argv[] = {"id", NULL};
		printf("Hello from child, my pid is %i\n", getpid());
		execve("/usr/bin/id", exec_argv, env); //execute a program
	} 
	else
	{
		int ret;
		wait(&ret); //wait for child's exit status
		printf("Hello from parent. My pid is %i, my child's pid is %i\n", getpid(), ch_pid);
		printf("Its exit status is %i\n", WEXITSTATUS(ret));
	}
	getchar();
}
