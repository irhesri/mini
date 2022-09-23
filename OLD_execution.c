/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:16 by imane             #+#    #+#             */
/*   Updated: 2022/09/23 18:54:12 by imane            ###   ########.fr       */
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

void	input_output_files(t_data *data, t_pipe *content, int *p)
{
	if (content->fd[0] != 0)
	{
		if (p[0])
			close(p[0]);
		p[0] = content->fd[0];
	}
	if (content->fd[1] != 1)
	{
		if (content->pipe_id != data->nbr_pipes)
			close(p[1]);
		p[1] = content->fd[1];
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
		input_output_files(data, content, p);
		if (p[0] != 0)
		{
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
		}
		if (content->fd[1] != 1 || content->pipe_id != data->nbr_pipes)
		{
			dup2(p[1], STDOUT_FILENO);
			close(p[1]);
		}
		commands_call(data, content->arg);
		exit(get_errno(-1));
	}
	return (id);
}

void	run_in_parent(t_data *data, t_pipe *content)
{
	int	in, out;

	out =dup(STDOUT_FILENO);
	if ((content->fd[0] < 0 || content->fd[1] < 0) && get_errno(1))
		return ;
	if (content->fd[0] != 0)
	{
		dup2(content->fd[0], STDIN_FILENO);
		close(content->fd[0]);
		content->fd[0] = -1;
	}
	if (content->fd[1] != 1)
	{
		dup2(content->fd[1], STDOUT_FILENO);
		close(content->fd[1]);
		content->fd[1] = -1;
	}
	commands_call(data, content->arg);
	dup2(out, STDOUT_FILENO);
}

void	run_commands(t_data *data, t_list *pipes)
{
	int		p1[2];
	int		p2[2];
	pid_t	id;
	t_node	*head;

	get_errno(0);
	head = pipes->head;
	if (data->nbr_pipes == 0 && is_builtin(*(((t_pipe *)(head->content))->arg)))
	{
		run_in_parent(data, head->content);
		dup2(1, STDOUT_FILENO);
		return ;
	}
	p2[0] = 0;
	while (head)
	{
		if (((t_pipe *)(head->content))->pipe_id != data->nbr_pipes)
			pipe(p1);
		p2[1] = p1[1];
		id = start_child(data, head->content, p2);
		(p2[0] > 0) && close(p2[0]);
		(head->next) && close(p2[1]);
		p2[0] = p1[0];
		head = head->next;
	}
	wait_for_children(id);
}
