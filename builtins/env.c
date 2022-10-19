/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:04 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/19 14:39:14 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initialise enviroment and export list

void	extra_env(t_data *data, char ***arr)
{
	char	*str;
	t_node	*node;

	node = getenv_node((get_env(NULL))->head, "PWD");
	if (!node)
	{
		str = malloc(sizeof(char) * MAXPATHLEN);
		if (str && getcwd(str, MAXPATHLEN))
		{
			str = free_join("PWD=", str, 2);
			*arr = array_realloc(*arr, str, -1);
		}
	}
	node = getenv_node((get_env(NULL))->head, "SHLVL");
	if (!node)
		*arr = array_realloc(*arr, my_strdup("SHLVL=1", '\0'), 0);
	else
	{
		str = node->content;
		str = free_join("SHLVL=", ft_itoa(ft_atoi(str + 6) + 1), 2);
		*arr = array_realloc(*arr, str, -1);
	}
	export(data, *arr);
}

void	init_env(t_data *data, char **envp)
{
	char	*str;
	char	**arr;

	while (envp && *envp)
	{
		if (**envp != '_' || (**envp && (*envp)[1] != '='))
		{
			str = my_strdup(*envp, '\0');
			add_node(get_env(NULL), (get_env(NULL))->last, str);
			add_node(get_exp(NULL),
				get_position((get_exp(NULL))->head, *envp), str);
		}
		envp++;
	}
	arr = array_realloc(NULL, my_strdup("OLDPWD", '\0'), 0);
	unset(data, arr);
	extra_env(data, &arr);
	free_arr(arr);
	str = my_strdup("_=/usr/bin/env", '\0');
	add_node(get_env(NULL), (get_env(NULL))->last, str);
	get_last(NULL, 1);
	update_envp(data);
}

// update **envp for excve if envp is null
void	update_envp(t_data *data)
{
	int		i;
	t_node	*head;

	if (data->envp)
		return ;
	data->envp = malloc(sizeof(char **) * ((get_env(NULL))->size + 1));
	head = (get_env(NULL))->head;
	i = -1;
	while (head)
	{
		data->envp[++i] = head->content;
		head = head->next;
	}
	data->envp[++i] = NULL;
}

short	update_path(t_data *data, char *str)
{
	free_arr(data->paths);
	if (!str || !*str)
		data->paths = NULL;
	else
		data->paths = my_split(str, ':', 1);
	free(str);
	return (1);
}

// print enviroment variables (env)
void	env(void)
{
	char	*str;
	t_node	*tmp;
	t_list	*env;

	get_errno(0);
	env = get_env(NULL);
	tmp = env->head;
	while (tmp)
	{
		str = ft_strjoin(tmp->content, "\n");
		ft_putstr(str, STDOUT_FILENO);
		free (str);
		tmp = tmp->next;
	}
}
