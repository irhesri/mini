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


	data = malloc(sizeof(t_data));
	init_env(data, envp);
	update_envp(data);


	// arg = malloc(sizeof(char *) * ac);
	// av++;
	// while (*av)
	// {
	// 	arg[i++] = my_strdup(*av, '\0');
	// 	av++;
	// }
	str = readline("-->");
	init_data(data, str);
	t_node	*tmp;
	tmp = (data->pipes)->head;
	// while (tmp)
	// {
		print_2D((char **)(((t_pipe *)(tmp->content))->arg));
		// tmp=tmp->next;
	// }
	// printf("%s - %s\n", my_strdup(av[1], '\0'), var_expand(data->env, my_strdup(av[1], '\0'), &i));
	print_pipes(data->pipes);

	
}
