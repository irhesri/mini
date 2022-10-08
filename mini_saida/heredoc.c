#include "../minishell.h"

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

short	chr_rp_var(char *line, int fd)
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
			write(fd, var, my_size(NULL, var));
			free(var);
		}
		else
			write(fd, &line[i], 1);
	}
	return (1);
}

short    heredoc(int fd, t_redirection *data)
{
	char    *line;
	int status;

	pid = fork();
	signal(SIGINT, handle_sigint);
	if (!pid)
	{   
		signal(SIGINT, handle_sigint);
		while (1)
		{
			line = readline("> ");
			if (!ft_strncmp(line, data->name, my_size(NULL, line) + 1))
				break ;
			data->fd == -2 && chr_rp_var(line, fd);
			data->fd == -3 && write(fd, line, my_size(NULL,line));
			free(line);
			line = NULL;
		}
		close(fd);
		exit(0);
	}
	wait(&status);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
		return (1);
	return (0);
}
