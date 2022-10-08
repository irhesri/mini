/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:24 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/08 16:58:47 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *data)
{
	t_list	*lst;

	data->pipes = malloc(sizeof(t_list));
	(data->pipes)->head = NULL;
	(data->pipes)->last = NULL;
	lst = malloc(sizeof(t_list));
	lst->head = NULL;
	lst->last = NULL;
	lst->size = 0;
	get_env(lst);
	lst = malloc(sizeof(t_list));
	lst->head = NULL;
	lst->last = NULL;
	lst->size = 0;
	get_exp(lst);
	data->envp = NULL;
	data->history = NULL;
	data->history_size = 0;
	data->history_lines = 0;
}

// initialise enviroment and export list
void	init_env(t_data *data, char **envp)
{
	char	*str;
	char	**arr;

	while (envp && *envp)
	{
		if (**envp != '_' || (**envp && (*envp)[1] != '='))
		{
			str = my_strdup(*envp, '\0');
			add_node(get_env(NULL), (get_env(NULL))->last, str);
			add_node(get_exp(NULL),
				get_position((get_exp(NULL))->head, *envp), str);
		}
		envp++;
	}
	arr = array_realloc(NULL, "OLDPWD", 0);
	unset(data, arr);
	export(data, arr);
	free (arr);
	str = my_strdup("_=/usr/bin/env", '\0');
	add_node(get_env(NULL), (get_env(NULL))->last, str);
	get_last(NULL, 1);
	update_envp(data);
}

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
			if (fd == -1)
				print_error(red->name, ": No such file or directory\n");
			return ;
		}
		lst = lst->next;
	}
}

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

short	init_files(t_data *data)
{
	t_node	*head;

	head = (data->pipes)->head;
	while (head)
	{
		if (check_for_here_docs(head->content))
			return (1);
		head = head->next;
	}
	head = (data->pipes)->head;
	while (head)
	{
		open_files(head->content);
		head = head->next;
	}
	return (0);
}
