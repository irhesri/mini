/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:04 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/08 13:02:44 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// update **envp for excve if envp is null
void	update_envp(t_data *data)
{
	int		i;
	t_node	*head;
	
	if (data->envp)
		return ;
	data->envp = malloc(sizeof(char **) * (get_env(NULL))->size);
	head = (get_env(NULL))->head;
	i = -1;
	while (head)
	{
		data->envp[++i] = head->content;
		head = head->next;
	}
}

// get enviroment variable data
char	*my_getenv(char *str)
{
	int		i;
	t_list	*env;
	t_node	*node;

	env = get_env(NULL);
	node = getenv_node(env->head, str);
	if (!node)
		return (NULL);
	str = (char *)node->content;
	i = my_search(str, '=');
	str = my_strdup(str + i + 1, '\0');
	return (str);
}

// print enviroment variables (env)
void	env(void)
{
	t_node	*tmp;
	t_list	*env;

	env = get_env(NULL);
	tmp = env->head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
