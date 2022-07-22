#include "minishell.h"

void	export_print(t_list *exp)
{
	int		i;
	t_node	*tmp;

	tmp = exp->head;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		i = my_search(tmp->str, '=');
		write(1, tmp->str, i);
		if (i > 0)
		{
			write(1, "=\"", 2);
			write(1, tmp->str + i + 1, my_size(NULL, tmp->str + i + 1));
			write(1, "\"\n", 2);
		}
		tmp = tmp->next;
	}
}

int	check_export(char *str)
{
	return (0);
}

void	export(t_data *data, char **str)
{
	int		i;

	if (!str || !*str)
	{
		export_print(data->exp);
		return ;
	}
	// while (*str)
	// {
	// 	// 2 exist whithout value
	// 	// 1 doesn't exist
	// 	if (check_export(*str) == 1 || check_export(*str) == 2)
	// 		add_node(data->env, *str, -1);
	// 	add_node(exp, *str, get_index(exp->head, *str));
	// 	str++;
	// }
	
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_env(data, envp);
	
	// env(data->env);
	// printf ("-----------------\n");
	// unset(data->exp, "__CF_USER_TEXT_ENCODING");
	export(data, av + 1);
	
}