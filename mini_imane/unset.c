#include "minishell.h"

static int	is_special(char c)
{		
	return (!(is_digit(c) || is_alphabet(c) 
			|| (c == '_')));
}

// b == 0 for unset
// b == 1 for export
// checks regular expression for unset and export
short	env_regex(char *str, short b)
{
	int			i;
	int			error;
	const char	*set[2];

	i = -1;
	error = (*str == '+' || *str == '=' || is_digit(*str));
	while (!error && str[++i])
	{
		if (b && str[i] == '=')
			break ;
		error = ((!b && str[i] == '+')
			|| (b && str[i] == '+' && str[i + 1] != '=')
			|| is_special(str[i]));
	}
	if (error)
	{
		set[0] = "unset";
		set[1] = "export";
		printf("minishell: %s: `%s': not a valid identifier\n", set[b], str);
		free (str);
	}
	return (error);
}

// delete node to_delete 
// get to_delete using getenv_node() function
void	delete_node(t_list *lst, t_node *to_delete)
{
	t_node	*tmp;
	t_node	*head;

	if (!lst->head || !to_delete)
		return ;
	lst->size--;
	if (lst->head == to_delete)
	{
		tmp = lst->head;
		lst->head = lst->head->next;
		if (!lst->head)
			lst->last = NULL;
	}
	head = lst->head;
	while (head->next != to_delete)
		head = head->next;
	tmp = head->next;
	head->next = tmp->next;
	if (!tmp->next)
		lst->last = head;
	free (tmp);
}

// like getenv() except that it returns pointer to a node
t_node	*getenv_node(t_node *head, char *str)
{
	char	*var;
	char	*content;
	size_t	size;

	var = my_strdup(str, '=');
	size = my_size(NULL, var);
	while (head)
	{
		content = head->content;
		if (!ft_strncmp(head->content, var, size)
			&& (content[size] == '=' || content[size] == '\0'))
			break ;
		head = head->next;
	}
	free (var);
	return (head);
}

// doesn't unset _
void	unset(t_data *data, char **arg)
{
	int		j;
	char	*tmp;
	t_node	*node;
	// while (arg && j++ < data->n)
	while (*arg)
	{
		if ((env_regex(*arg, 0) || (**arg == '_' && !*(arg + 1))) && arg++)
			continue ;
		node = getenv_node(data->exp->head, *arg);
		if (node)
		{
			tmp = node->content;
			delete_node(data->exp, node);
			node = getenv_node(data->env->head, *arg);
			if (node)
			{
				delete_node(data->env, node);
				if (data->envp)
					free (data->envp);
				data->envp = NULL;
			}
			free (tmp);
		}
		free (*arg++);
	}
}
