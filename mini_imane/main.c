#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_data	*data;

// 	data = malloc(sizeof(t_data));
// 	init_env(data, envp);

// 	update_envp(data);

// 	char	**arg;

// 	arg = malloc(sizeof(char*) * (ac + 1));
// 	int i = -1;
// 	av++;
// 	while (++i < ac - 1)
// 	{
// 		arg[i] = my_strdup(av[i], '\0');
// 		// printf("%s\n", arg[i]);

// 		// av[i];
// 	}
// 	arg[i] = NULL;
	
// 	export (data, arg);
// 	arg[0] = my_strdup(av[0], '\0');
// 	unset(data, arg);
// 	// char *str = my_strdup("hhhhhhh", '\0');
// 		// printf("%s\n", str);

// 	// int len = 1;

// 	// char **res = array_realloc(arg, str, 0);
// 	// i = -1;
// 	// while (res[++i])
// 	// {
// 	// // 	len = 0;
// 	// // 	printf("%s\n", expand(data->env, arg[i], &len));
// 	// 	// printf("%s\n", res[i]);

// 	// }
// 	// env(data->env);
// }


int	main(int ac, char **av, char **envp)
{
	char	**arg;
	char	*str;
	int	i = 0;
	t_data *data;
	
	t_list	*e;

	data = malloc(sizeof(t_data));
	init_data(data, str);
	init_env(data, envp);
	get_env(data->env);
	while (1)
	{
		str = readline("---->  ");
		parse_time (data, str);
		print_pipes(data, data->pipes);
		free (str);
		export(data, ((t_pipe *)(((data->pipes)->head)->content))->arg);
		// unset(data, ((t_pipe *)(((data->pipes)->head)->content))->arg);
		// print_list(data->exp);
		export(data, NULL);
		empty_pipes(data->pipes);
	}

	// e = data->env;
	// free_all(data);
	data = NULL;
	// while (1);
	// {
	// 	;
	// }
	
	
}
