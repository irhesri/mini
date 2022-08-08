/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:13:36 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/08 13:02:44 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe	*new_pipe(t_data *data, short b)
{
	t_pipe		*pipe;
	static int	id;

	if (b)
		id = 0;
	data->nbr_pipes = id;
	if (id != 0)
		get_last(NULL, 1);
	pipe = malloc(sizeof(t_pipe));
	pipe->pipe_id = id++;
	pipe->arg = NULL;
	pipe->n = 0;
	pipe->input = malloc(sizeof(t_list));
	(pipe->input)->head = NULL;
	pipe->output = malloc(sizeof(t_list));
	(pipe->output)->head = NULL;
	add_node(data->pipes, (data->pipes)->last, pipe);
	return (pipe);
}

char	*new_argument(t_pipe *pipe, char **res2, char *res)
{
	char	**tmp;

	if (res2)
	{
		tmp = res2;
		res = free_join(res, *res2, 0);
		while (*res2 && *(res2 + 1))
		{
			pipe->arg = array_realloc(pipe->arg, res, -1);
			pipe->n++;
			res = *(++res2);
		}
		free (tmp);
		return (res);
	}
	if (res && !*res)
		free (res);
	else if (res)
	{
		pipe->arg = array_realloc(pipe->arg, res, -1);
		pipe->n++;
		if (pipe->pipe_id == 0)
			get_last(my_strdup(res, '\0'), 1);
	}
	return (NULL);
}

