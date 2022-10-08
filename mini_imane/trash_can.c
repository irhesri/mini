/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:52 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/07 23:56:52 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_red_list(t_list *lst)
{
	t_node			*node;
	t_node			*tmp;
	t_redirection	*file;

	node = lst->head;
	while (node)
	{
		tmp = node->next;
		file = node->content;
		free(file->name);
		if (file->fd > 1)
			close (file->fd);
		free (file);
		free (node);
		node = tmp;
	}
	free (lst);
}

void	empty_pipes(t_list *pipes_lst)
{
	char	**args;
	t_node	*pipe;
	t_node	*tmp;

	pipe = pipes_lst->head;
	pipes_lst->head = NULL;
	pipes_lst->last = NULL;
	while (pipe)
	{
		tmp = pipe->next;
		args = ((t_pipe *)(pipe->content))->arg;
		while (args && *args)
			free (*args++);
		free (((t_pipe *)(pipe->content))->arg);
		free_red_list(((t_pipe *)(pipe->content))->redirections);
		free(pipe->content);
		free (pipe);
		pipe = tmp;
	}
}

void	free_list(t_list *lst, short b)
{
	t_node	*node;
	t_node	*tmp;

	node = lst->head;
	while (node)
	{
		tmp = node->next;
		if (b || !ft_strncmp(node->content, "_=", 2))
			free(node->content);
		free (node);
		node = tmp;
	}
	free(lst);
}

void	free_all(t_data *data)
{
	empty_pipes(data->pipes);
	free (data->pipes);
	free (data->envp);
	free_list(get_env(NULL), 0);
	free_list(get_exp(NULL), 1);
	display_history(NULL);
	free_arr(data->history);
	free (data);
}

void	free_arr(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (arr && *arr)
		free (*arr++);
	free (tmp);
}
