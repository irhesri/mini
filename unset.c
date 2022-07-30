#include "minishell.h"

static int	_is_special(char c)
{		
	return (!((c > 47 && c < 58) || (c > 64 && c < 91)
			|| (c > 96 && c < 123) || (c == 43)
			|| (c == 95) || (c == 61)));
}

// b == 0 for unset
// b == 1 for export
// checks regular expression for unset and export
int	env_regex(char *str, short b)
{
	int			i;
	int			size;
	int			error;
	const char	*set[2];

	error = 0;
	set[0] = "unset";
	set[1] = "export";
	if (*str == '+' || *str == '=' || (*str > 47 && *str < 58))
		error = 1;
	i = 0;
	while (!error && str[i] && str[i + 1] != '=')
	{
		if ((!b && (str[i] == 43 || str[i] == 61))
			|| (b && str[i] == 43 && str[i + 1] != '=')
			|| _is_special(str[i]))
			error = 1;
		i++;
	}
	if (error)
	{
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
