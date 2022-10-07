#include "../minishell.h"
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid;

void handle_sigint(int sig)
{
    if (pid)
        kill(pid, SIGINT);
    else
        exit (1);
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
        }
        else
            write(fd, &line[i], 1);
    }
    return (1);
}

void    heredoc(t_pipe *data, t_redirection *n)
{
	char    *line;
    int status;
   
	pipe(data->fd);
    pid = fork();
    signal(SIGINT, handle_sigint);
	if (!pid)
	{   
        close(data->fd[0]);
        signal(SIGINT, handle_sigint);
		while (1)
		{
			line = readline("> ");
			if (!strcmp(line, n->name) || !(*line))
				break ;
			data->fd == -2 && chr_rp_var(line, data->fd[1]);
			data->fd && write(data->fd[1], line, strlen(line));
			free(line);
			line = NULL;
		}
        close(data->fd[1]);
        exit(0);
	}
    wait(&status);
    if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
    {
        close (data->fd[0]);
        // rl_on_new_line ();
    }
    else
        close(data->fd[1]);
    // char *k;
    // k = malloc(6);
    // close(fd[1]);
    // // // close(fd_data->fd[1]);
    // read(fd[0], k, 5);
    // write(1, k, 5);
}
