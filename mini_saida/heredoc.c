#include "../minishell.h"
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid = -2;

void handle_sigint(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	if (pid > 0)
		kill(pid, SIGINT);
	else if (!pid)
		exit (1);
	rl_on_new_line();
	rl_redisplay();	
}

int    chr_rp_var(char *line, int fd)
{
	int     i;
	// char    c;
	char    *var;

	i = -1;
	while(line[++i])
	{
		if (line[i] == '$')
		{
			var = var_expand(line, &i);
			write(fd, var, strlen(var));
			free(var);
		}
		else
			write(fd, &line[i], 1);
	}
	return (1);
}+

void    heredoc(int *fd, char name/*t_pipe *data, t_redirection *n*/)
{
	char    *line;
	int status;

	pipe(fd);
	pid = fork();
	signal(SIGINT, handle_sigint);
	if (!pid)
	{   
		close(fd[0]);
		signal(SIGINT, handle_sigint);
		while (1)
		{
			line = readline("> ");
			if (!strcmp(line, &name) )//|| !(*line))
				break ;
			data->fd == -2 && chr_rp_var(line, fd[1]);
			write(fd[1], line, strlen(line));
			free(line);
			line = NULL;
		}
		close(fd[1]);
		exit(0);
	}
	wait(&status);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
	{
		close(fd[1]);
		close(fd[0]);
	}
	else
		close(fd[1]);
}
