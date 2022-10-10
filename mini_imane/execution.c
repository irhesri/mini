/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:16 by imane             #+#    #+#             */
/*   Updated: 2022/10/10 10:57:38 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	commands_call(t_data *data, char **arg)
{
	short		b;
	static void	(*ptr[9])();

	if (!ptr[0])
	{
		ptr[0] = not_builtin;
		ptr[1] = export;
		ptr[2] = unset;
		ptr[3] = my_exit;
		ptr[4] = cd;
		ptr[5] = history;
		ptr[6] = env;
		ptr[7] = echo;
		ptr[8] = pwd;
	}
	if (!arg || !*arg)
		return ;
	b = is_builtin(*arg);
	if (b < 6 && arg)
		ptr[b](data, arg + (b != 0));
	else
		ptr[b](arg + 1);
}

pid_t	start_child(t_data *data, t_pipe *content, int *p)
{
	pid_t	id;

	id = fork();
	if (!id)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (content->fd[0] < 0 || content->fd[1] < 0)
			free_exit(data, 1);
		if (p && p[0] > 0)
			close (p[0]);
		if (content->fd[0] != 0)
			my_dup2(content->fd, STDIN_FILENO);
		if (content->fd[1] != 1)
			my_dup2(content->fd + 1, STDOUT_FILENO);
		commands_call(data, content->arg);
		free_exit(data, get_errno(-1));
	}
	return (id);
}

void	wait_for_children(pid_t id)
{
	int		n;
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		if (WIFEXITED(status))
			n = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		// {
			n = 128 + WTERMSIG(status);
		// 	write(1, "\n", 1);
		// }
		if (id == pid)
			get_errno(n);
	}
	signal(SIGINT, handle_sigint);
}

void	one_command_line(t_data *data, t_pipe *content, int *fd)
{
	pid_t	pid;

	if (content->arg && *content->arg && is_builtin(*(content->arg)))
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
		pid = start_child(data, content, NULL);
		wait_for_children(pid);
	}
}

void	run_commands(t_data *data, t_list *pipes)
{
	int		p[2];
	int		fd[2];
	pid_t	pid;
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
		pid = start_child(data, head->content, p);
		my_dup2(p, STDIN_FILENO);
		head = head->next;
	}
	my_dup2(fd, STDIN_FILENO);
	wait_for_children(pid);
}