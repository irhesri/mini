/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:16 by imane             #+#    #+#             */
/*   Updated: 2022/09/23 20:02:57 by imane            ###   ########.fr       */
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

void	input_output_files(int *fd)
{
	if (fd[0] != 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		fd[1] = -1;
	}
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
		input_output_files(content->fd);
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
		input_output_files(content->fd);
		commands_call(data, content->arg);
		input_output_files(fd);
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
	t_pipe	*content;

	get_errno(0);
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	head = pipes->head;
	if (data->nbr_pipes == 0)
	{
		one_command_line(data, head->content, fd); //return
		return ;
	}
	while (head)
	{
		content = head->content;
		if (content->pipe_id != data->nbr_pipes)
			pipe(p);
		else
			p[1] = fd[1];
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		id = start_child(data, head->content, p);
		if (head->next)
		{
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			p[0] = -1;
		}
		head = head->next;
	}
	wait_for_children(id);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
