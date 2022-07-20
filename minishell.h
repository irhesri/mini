#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	char	**env;					//init envp
	char	**sorted_env;
	short	b;						//init 1
	size_t	env_size;
}	t_data;

// size_t	my_strlen(char *str);
short	my_strncmp(char *str1, char *str2, size_t n);
size_t	my_size(char **arr, char *str, short b);

#endif