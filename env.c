#include "minishell.h"

void	env(t_list *env)
{
	t_node	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_data	*data;

// 	data = malloc(sizeof(t_data));

// 	init_env(data, envp);
// 	env(data->env);
	
// }