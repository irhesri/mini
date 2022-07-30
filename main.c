#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_env(data, envp);

	update_envp(data);
	
	// printf ("-----------------\n");
	// unset(data->exp, "__CF_USER_TEXT_ENCODING");
	char	**arg;

	arg = malloc(sizeof(char*) * (ac + 1));
	int i = -1;
	av++;
	while (++i < ac - 1)
	{
		arg[i] = my_strdup(*av, '\0');
		// printf("%s\n", arg[i]);

		av++;
	}
	arg[i] = NULL;
	
	int len = 1;
	i = -1;
	while (arg[++i])
	{
		len = 0;
		printf("%s\n", expand(data->env, arg[i], &len));
		printf("%d\n", len);
	}
	// env(data->env);
	
}
