#include "../mini_imane/minishell.h"
//	prints enviroment variables 
static short	export_print(t_list *exp)
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
	return (1);
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

// updates an exiting variable
void	update_var(t_data *data, t_node *node, char *str, int i)
{
	char	*tmp;

	if (str[i - 1] == '\0')
		str = ft_strjoin(node->content, str + i + (my_search(node->content, '=') != -1));
	else
		str = my_strdup(str, '\0');
	tmp = node->content;
	node->content = str;
	node = getenv_node((get_env(NULL))->head, str);
	if (node)
	{
		node->content = str;
		free (data->envp);
		data->envp = NULL;
	}
	else
		add_node(get_env(NULL), (get_env(NULL))->last, str);
	free (tmp);
}

// add a new variable
void	new_var(t_data *data, char *str, int i)
{
	if (i != -1 && str[i - 1] == '\0')
		str = ft_strjoin(str, str + i);
	else
		str = my_strdup(str, '\0');
	add_node(get_exp(NULL), get_position((get_exp(NULL))->head, str), str);
	if (i != -1)
		add_node(get_env(NULL), (get_env(NULL))->last, str);
}

// exports arg
// prints enviroment variables if arg is NULL (export)
void	export(t_data *data, char **arg)
{
	int		i;
	int		j;
	t_node	*node;

	if ((!arg || !*arg) && export_print(get_exp(NULL)))
		return ;
	while (*arg)
	{
		if (env_regex(*arg, 1) && arg++)
			continue ;
		i = my_search(*arg, '=');
		if (i != -1 && ((*arg)[i - 1] == '+'))
			(*arg)[i - 1] = '\0';
		get_last(my_strdup(*arg, '='), 1);
		if (**arg == '_' && ((*arg)[1] == '=' || (*arg)[1] == '\0') && arg++)
			continue ;
		node = getenv_node((get_exp(NULL))->head, *arg);
		if (!node)
			new_var(data, *arg, i);
		else if (i != -1)
			update_var(data, node, *arg, i);
		arg++;
	}
}
