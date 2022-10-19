/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:24 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/19 22:16:57 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_error(char *file, int fd)
{
	if (fd == -4)
		print_error(file, ": ambiguous redirect\n");
	else if (is_directory(file))
		print_error(file, ": Is a directory\n");
	else
		print_error(file, ": No such file or directory\n");
}

// open files in pipe and updating pipe->fd[0/1]
void	open_files(t_pipe *pipe)
{
	int				fd;
	t_node			*lst;
	t_redirection	*red;

	lst = (pipe->redirections)->head;
	while (lst)
	{
		red = lst->content;
		if (!red->mode && !red->fd)
			fd = open(red->name, O_RDONLY);
		else if (red->mode && !red->fd)
			fd = open(red->name, O_CREAT | O_WRONLY | red->mode, 0644);
		else
			fd = red->fd;
		pipe->fd[(red->mode != 0)] = fd;
		if (fd < 0)
		{
			file_error(red->name, fd);
			return ;
		}
		lst = lst->next;
	}
}

// starting all here_docs in the pipe (red->fd == -2/-3)
short	check_for_here_docs(t_pipe *pip)
{
	int				error;
	int				p[2];
	t_node			*lst;
	t_redirection	*red;

	lst = (pip->redirections)->head;
	while (lst)
	{
		red = lst->content;
		if (red->fd < -1 && red->fd > -4)
		{
			pipe(p);
			error = heredoc(p[1], red);
			close(p[1]);
			if (error)
			{
				close (p[0]);
				return (error);
			}
			red->fd = p[0];
		}
		lst = lst->next;
	}
	return (0);
}

// starting all here_docs in the line
short	init_here_doc(t_data *data)
{
	t_node	*head;

	head = (data->pipes)->head;
	while (head)
	{
		if (check_for_here_docs(head->content))
			return (1);
		head = head->next;
	}
	return (0);
}

// open files after starting heredocs
short	init_files(t_data *data)
{
	t_node	*head;

	if (init_here_doc(data) == 1)
		return (1);
	head = (data->pipes)->head;
	while (head)
	{
		open_files(head->content);
		head = head->next;
	}
	return (0);
}
