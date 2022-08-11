/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_can.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:52 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/11 12:55:07 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	empty_pipes(t_list *pipes_lst)
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
		if (file->fd > 0)
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
		if (b)
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
	delete_node(get_env(NULL), getenv_node((get_env(NULL))->head, "_"));
	free_list(get_env(NULL), 0);
	free_list(get_exp(NULL), 1);
	free (data);
}
