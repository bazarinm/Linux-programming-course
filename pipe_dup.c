#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *env[])
{
	pid_t ch_pid;
	int pipefd[2], count = 1;
	char buf[256];
	pipe(pipefd);
	if((ch_pid = fork()) == 0) //child process
	{
		close(pipefd[0]);
		close(1);
		dup2(pipefd[1], 1);
		return execve(argv[1], argv + 1, env); //execute a program
	} 
	else
	{
		int ch_exit;
		close(pipefd[1]);
		while(count > 0) 
		{
			count = read(pipefd[0], buf, sizeof(buf));
			write(1, buf, count);
		}
		wait(&ch_exit); //wait for child's exit status
		exit(WEXITSTATUS(ch_exit));
	}
}
