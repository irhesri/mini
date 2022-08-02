#include "minishell.h"
//	prints enviroment variables 
static void	export_print(t_list *exp)
{
	int		i;
	t_node	*tmp;

	tmp = exp->head;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		i = my_search(tmp->content, '=');
		if (i < 0)
			i = my_size(NULL, tmp->content);
		write(1, tmp->content, i + 1);
		if (((char *)(tmp->content))[i])
		{
			write(1, "\"", 1);
			write(1, tmp->content + i + 1, my_size(NULL, tmp->content + i + 1));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

// get position of new variable in export list (sorted)
t_node	*get_position(t_node *head, char *str)
{
	size_t	size;
	t_node	*pos;

	size = my_size(NULL, str) + 1;
	if (!head || ft_strncmp(head->content, str, size) > 0)
		return (NULL);
	pos = head;
	head = head->next;
	while (head && (ft_strncmp(head->content, str, size) < 0))
	{
		pos = head;
		head = head->next;
	}
	return (pos);
}

// add a new variable
void	new_var(t_data *data, t_node *node, char *str, int i)
{
	char	*tmp;

	if (str[i - 1] == '\0')
	{
		tmp = str;
		str = ft_strjoin(node->content, tmp + i + 1);
		free (tmp);
	}
	tmp = node->content;
	node->content = str;
	node = getenv_node(data->env->head, str);
	if (node)
		node->content = str;
	if (node && data->envp)
	{
		free (data->envp);
		data->envp = NULL;
	}
	free(tmp);
}

// updates an exiting variable
void	update_var(t_data *data, char *str, int i)
{
	char	*tmp;

	if (i != -1 && str[i - 1] == '\0')
	{
		tmp = str;
		str = ft_strjoin(tmp, tmp + i);
		free (tmp);
	}
	add_node(data->exp, get_position(data->exp->head, str), str);
	if (i != -1)
		add_node(data->env, data->env->last, str);
}

// exports arg
// prints enviroment variables if arg is NULL (export)
void	export(t_data *data, char **arg)
{
	int		i;
	int		j;
	char	*tmp;
	t_node	*node;

	if (!arg)
		export_print(data->exp);
	// while (arg && j++ < data->n)
	while (arg && *arg)
	{
		if (env_regex(*arg, 1) && arg++)
			continue ;
		tmp = *arg;
		i = my_search(*arg, '=');
		if (i != -1 && ((*arg)[i - 1] == '+'))
			(*arg)[i - 1] = '\0';
		node = getenv_node(data->exp->head, *arg);
		if (!node)
			update_var(data, *arg, i);
		else if (i != -1)
			new_var(data, node, *arg, i);
		free (*arg);
		arg++;
	}
}

// free (*arg);
// free (arg);
