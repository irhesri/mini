#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	struct stat buf;
	char	*s[] = {"ls", "-la", NULL};
	printf("%d\n",  stat("ls", &buf));
	printf("%d\n",  buf.st_mode == S_IFDIR);
	// printf("%d\n",  stat("cat", buf));
	// execve("ls", s, envp);
	// perror("ls");
}
