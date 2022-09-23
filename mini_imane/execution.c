/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:16 by imane             #+#    #+#             */
/*   Updated: 2022/09/23 20:25:11 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(pid_t id)
{
	int		n;
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		if (WIFEXITED(status))
			n = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			n = 128 + WTERMSIG(status);
		if (id == pid)
			get_errno(n);
	}
}

int	my_dup2(int *newfd, int oldfd)
{
	if (*newfd < 0)
		return (-1);
	if (dup2(*newfd, oldfd) == -1)
		return (-1);
	close(*newfd);
	(*newfd) = -1;
	return (1);
}

pid_t	start_child(t_data *data, t_pipe *content, int *p)
{
	char	**command;
	char	*path;
	pid_t	id;

	id = fork();
	if (!id)
	{
		if (content->fd[0] < 0 || content->fd[1] < 0)
			exit(1);
		if (p && p[0] > 0)
			close (p[0]);
		if (content->fd[0] != 0)
			my_dup2(content->fd, STDIN_FILENO);
		if (content->fd[1] != 1)
			my_dup2(content->fd + 1, STDOUT_FILENO);
		commands_call(data, content->arg);
		exit(get_errno(-1));
	}
	return (id);
}

void	one_command_line(t_data *data, t_pipe *content, int *fd)
{
	pid_t	id;

	if (is_builtin(*(content->arg)))
	{
		if (content->fd[0] < 0 || content->fd[1] < 0)
		{
			get_errno(1);
			return ;
		}
		if (content->fd[0] != 0)
			my_dup2(content->fd, STDIN_FILENO);
		if (content->fd[1] != 1)
			my_dup2(content->fd + 1, STDOUT_FILENO);
		commands_call(data, content->arg);
		my_dup2(fd, STDIN_FILENO);
		my_dup2(fd + 1, STDOUT_FILENO);
	}
	else
	{
		id = start_child(data, content, NULL);
		wait_for_children(id);
	}
}

void	run_commands(t_data *data, t_list *pipes)
{
	int		p[2];
	int		fd[2];
	pid_t	id;
	t_node	*head;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	head = pipes->head;
	if (data->nbr_pipes == 0)
	{
		one_command_line(data, head->content, fd);
		return ;
	}
	while (head)
	{
		p[1] = fd[1];
		if (((t_pipe *)head->content)->pipe_id != data->nbr_pipes)
			pipe(p);
		my_dup2(p + 1, STDOUT_FILENO);
		id = start_child(data, head->content, p);
		my_dup2(p, STDIN_FILENO);
		head = head->next;
	}
	wait_for_children(id);
	my_dup2(fd, STDIN_FILENO);
}
