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
		av++;
	}
	arg[i] = NULL;
	i = -1;
	int x;
	int j;
	while (++i < ac - 1)
	{
		printf("%s\n", var_expand(data->env, arg[i] + 1, &j));

		// printf("%s\n", get_var_data(my_getenv(data->env->head, arg[i])));
		
		// printf("---2-----: %s\n", arg[i] + x);
		// printf("---2-----: %s\n", arg[i]);
	}
	// export(data, arg);
	// env(data->env);
	// unset(data, arg);
	// export(data, NULL);
	// arg = NULL;
	// while (1)
	// {
	// 	;
	// }
}
