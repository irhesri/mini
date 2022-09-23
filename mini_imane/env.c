/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:04 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/23 21:50:37 by imane            ###   ########.fr       */
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
		ft_putstr(str);
		free (str);
		tmp = tmp->next;
	}
}
