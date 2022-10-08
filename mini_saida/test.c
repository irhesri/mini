#include "../minishell.h"
/*
void handle_sigint(int sig)
{
	char *line;
	int i;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
//	signal(SIGINT, handle_sigint);
	
//	line = readline("$$ ");
//	exit(0);
}

int main()
{
	char *line;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		line = readline("$$ ");
			//	rl_on_new_line_with_promp();
		add_history(line);
	//	printf("your line: %s\n", line);
	}
}*/

/*int main()
{
	char *line;
	int	fd[2];

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		line = readline("$$ ");
	//	if (line[0] == 'h')
	//		heredoc(fd, 'h');
	//	line = malloc(6);
	//	read(fd[0], line, 5);
		add_history(line);
	//	printf("your line: %s\n", line);
	}
}*/
