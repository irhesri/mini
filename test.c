
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include <sys/param.h>
# include <string.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

void	replace(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	signal(SIGINT, replace);
	while (1)
	{
		str = readline(">>>> ");
		add_history(str);
	}
	

}