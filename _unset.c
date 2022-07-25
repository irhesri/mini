#include "minishell.h"

int	is_special(char c)
{		
	return (!((c > 47 && c < 58) || (c > 64 && c < 91)
			|| (c > 96 && c < 123) || (c == 43)
			|| (c == 95) || (c == 61)));
}

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
			||is_special(str[i]))
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

//	CHANGE	IT 
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

t_node	*my_getenv(t_node *head, char *str)
{
	char	*var;
	size_t	size;

	var = my_strdup(str, '=');
	size = my_size(NULL, var);
	while (head)
	{
		if (!my_strncmp(head->str, var, size)
			&& (head->str[size] == '=' || head->str[size] == '\0'))
			break ;
		head = head->next;
	}
	free (var);
	return (head);
}

void	unset(t_data *data, char **arg)
{
	char	*tmp;
	t_node	*node;

	while (*arg)
	{
		if (env_regex(*arg, 0) && arg++)
			continue ;
		node = my_getenv(data->exp->head, *arg);
		if (node)
		{
			tmp = node->str;
			delete_node(data->exp, node);
			node = my_getenv(data->env->head, *arg);
			if (node)
			{
				delete_node(data->env, node);
				if (data->envp)
					free (data->envp);
				data->envp = NULL;
			}
			free (tmp);
		}
		free (*arg);
		arg++;
	}
}
