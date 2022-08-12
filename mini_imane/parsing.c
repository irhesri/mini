/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:48 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/12 15:36:04 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	is_limiter(char *c)
{
	int			i;
	short		b;
	static char s[10] = "\'\"$| <<>";

	b = 0;
	i = -1;
	while (!b && ++i < 8)
		b = (s[i] == *c) * (i + 1);
	if (b > 4)
		return (b + (*(c + 1) == *c));
	return (b);
}

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
	pipe->fd[0] = 0;
	pipe->fd[1] = 1;
	pipe->redirections = malloc(sizeof(t_list));
	(pipe->redirections)->head = NULL;
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
	else if (res)
	{
		pipe->arg = array_realloc(pipe->arg, res, -1);
		pipe->n++;
		if (pipe->pipe_id == 0)
			get_last(my_strdup(res, '\0'), 1);
	}
	return (NULL);
}

char	*parse_time_2(char *str, char *res, int *i, int tmp)
{
	if (!tmp)
	{
		tmp = *i;
		while (str[*i] && !is_limiter(str + *i))
			(*i)++;
		res = free_join(res, my_strdup(str + tmp, str[*i]), 0);
	}
	else if (tmp == 1 && ++(*i))
		res = free_join(res, is_quoted(str, i, 39), 0);
	else if (tmp == 2 && ++(*i))
		res = free_join(res, is_double_quoted(str, i), 0);
	return (res);
}

//	EMPTY PIPES.
void	parse_time(t_data *data, char *str)
{
	int		i;
	int		tmp;
	t_pipe	*pipe;
	char	*res;

	i = 0;
	pipe = new_pipe(data, 1);
	res = NULL;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		tmp = is_limiter(str + i);
		if (tmp < 3)
			res = parse_time_2(str, res, &i, tmp);
		else if (tmp == 3 && ++i)
			res = new_argument(pipe, split_expand(str, &i), res);
		else if (tmp > 5)
			is_redirection(pipe, str, &i, tmp);
		if (tmp == 4 || !str[i] || is_limiter(str + i) > 3)
			res = new_argument(pipe, NULL, res);
		if (tmp == 4 && ++i)
			pipe = new_pipe(data, 0);
	}
}


