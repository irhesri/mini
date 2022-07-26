/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:52 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/19 22:22:45 by imane            ###   ########.fr       */
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

// free data->pipes and its content + closes the open fds
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

// free double pointer and return NULL
char	**free_arr(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (arr && *arr)
		free (*arr++);
	free (tmp);
	return (NULL);
}
