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
		if (i < 0)
			i = my_size(NULL, tmp->str);
		write(1, tmp->str, i + 1);
		if (tmp->str[i])
		{
			write(1, "\"", 1);
			write(1, tmp->str + i + 1, my_size(NULL, tmp->str + i + 1));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

t_node	*get_position(t_node *head, char *str)
{
	size_t	size;
	t_node	*pos;

	size = my_size(NULL, str) + 1;
	if (!head || my_strncmp(head->str, str, size) > 0)
		return (NULL);
	pos = head;
	head = head->next;
	while (head && (my_strncmp(head->str, str, size) < 0))
	{
		pos = head;
		head = head->next;
	}
	return (pos);
}

void	new_var(t_data *data, t_node *node, char *str, int i)
{
	char	*tmp;

	if (str[i - 1] == '\0')
	{
		tmp = str;
		str = my_strjoin(node->str, tmp + i + 1);
		free (tmp);
	}
	tmp = node->str;
	node->str = str;
	node = my_getenv(data->env->head, str);
	if (node)
		node->str = str;
	if (node && data->envp)
	{
		free (data->envp);
		data->envp = NULL;
	}
	free(tmp);
}

void	update_var(t_data *data, char *str, int i)
{
	char	*tmp;

	if (i != -1 && str[i - 1] == '\0')
	{
		tmp = str;
		str = my_strjoin(tmp, tmp + i);
		free (tmp);
	}
	add_node(data->exp, get_position(data->exp->head, str), str);
	if (i != -1)
		add_node(data->env, data->env->last, str);
}

void	export(t_data *data, char **arg)
{
	int		i;
	char	*tmp;
	t_node	*node;

	if (!arg)
		export_print(data->exp);
	while (arg && *arg)
	{
		if (env_regex(*arg, 1) && arg++)
			continue ;
		tmp = *arg;
		i = my_search(*arg, '=');
		if (i != -1 && ((*arg)[i - 1] == '+'))
			(*arg)[i - 1] = '\0';
		node = my_getenv(data->exp->head, *arg);
		if (!node)
			update_var(data, *arg, i);
		else if (i != -1)
			new_var(data, node, *arg, i);
		arg++;
	}
}
