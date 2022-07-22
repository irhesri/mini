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
	char	*find;
	t_node	*node;

	if (!str || !*str)
	{
		export_print(data->exp);
		return ;
	}
	while (*str)
	{
		find = my_strdup(str, '=');
		i = my_search(str, '=');
		node = my_getenv(data->exp->head, find);
		if (!node)
			add_node(data->exp, get_position(data->exp->head, find), str);
		else
		{
			if (str[i - 1])
			free (node->str);
			node->str = str;
		}
		if (!node && i >= 0)
			add_node(data->env, -1, str);
		else if (i >= 0)
		{
			node = my_getenv(data->env->head, find);
			free (node->str);
			node->str = str;
		}
		if (i >= 0)
			data->b = 1;
		str++;
	}
	
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