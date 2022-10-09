/*#include "../minishell.h"

short   chr_rp_var(char *line, int fd)
{
    int     i;

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

void    my_wait()
{
    int status;

    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    wait(&status);
    if (WTERMSIG(status) && WIFSIGNALED(status))
    {
        get_errno(1);
        write(1, "\n", 1);
    }
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, handle_sigint);
}

int main()
{
    char    *line;
    int     len;
	int fd[2];

	pipe(fd);
    get_errno(0);
    if (!fork())
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
        while (1)
        {
            line = readline("> ");
            len = my_size(NULL,line);
            if (!line || !ft_strncmp(line, "h", len + 1))
                break ;
            write(fd[1], line, len);
            write(fd[1], "\n", 1);
            free(line);
            line = NULL;
        }
        close(fd[1]);
        exit(0);
    }
	close(fd[1]);
    my_wait();
    return (get_errno(-1));
}*/
