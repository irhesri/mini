/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:55 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/23 22:04:48 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_special(char c)
{		
	return (!(is_alphanum(c)
			|| (c == '+') || (c == '_')));
}

// b == 0 for unset
// b == 1 for export
// checks regular expression for unset and export
short	env_regex(char *str, short b)
{
	int			i;
	int			error;
	char		*tmp;
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
		set[0] = "unset: `";
		set[1] = "export: `";
		get_errno(1);
		tmp = ft_strjoin((char *)set[b], str);
		print_error(tmp, "': not a valid identifier\n");
		free(tmp);
	}
	return (error);
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
	char	*tmp;
	t_node	*node;

	while (arg && *arg)
	{
		if ((env_regex(*arg, 0) || (**arg == '_' && !((*arg)[1]))) && arg++)
			continue ;
		node = getenv_node((get_exp(NULL))->head, *arg);
		if (node)
		{
			tmp = node->content;
			delete_node(get_exp(NULL), node);
			node = getenv_node((get_env(NULL))->head, *arg);
			if (node)
			{
				delete_node(get_env(NULL), node);
				free (data->envp);
				data->envp = NULL;
			}
			free (tmp);
		}
		arg++;
	}
}
