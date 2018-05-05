#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *env[])
{
	pid_t ch_pid;
	int pipefd[2], count;
	char buf[256];
	pipe(pipefd);
	if((ch_pid = fork()) == 0) //child process
	{
		const char *str = "Hello from child!\n";
		write(pipefd[1], str, strlen(str));
	} 
	else
	{
		int ch_exit;
		count = read(pipefd[0], buf, sizeof(buf));
		write(1, buf, count);
		wait(&ch_exit); //wait for child's exit status
	}
}
