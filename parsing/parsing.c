/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:48 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/22 03:04:10 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initialise a pipe and add it to data->pipes
t_pipe	*new_pipe(t_data *data, short b)
{
	t_pipe		*pipe;
	static int	id;

	if (b)
		id = 0;
	data->nbr_pipes = id;
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

// add res or res2 to pipe->arg
char	*new_argument(t_pipe *pipe, char **res2, char *res, short b)
{
	char	**tmp;

	if (b && res2)
	{
		tmp = res2;
		res = free_join(res, *res2, 0);
		while (*res2 && *(res2 + 1))
		{
			pipe->arg = array_realloc(pipe->arg, res, -1);
			pipe->n++;
			res = *(++res2);
		}
		free(tmp);
	}
	else if (!b && res)
	{
		pipe->arg = array_realloc(pipe->arg, res, -1);
		pipe->n++;
		return (NULL);
	}
	return (res);
}

// case of string + single/double quote
short	parse_time_2(char *str, char **res, int *i, int tmp)
{
	char	*string;

	string = NULL;
	if (!tmp)
	{
		tmp = *i;
		while (str[*i] && !is_limiter(str + *i)
			&& str[*i] != '\t' && str[*i] != '\n')
			(*i)++;
		(*res) = free_join(*res, my_strdup(str + tmp, str[*i]), 0);
		return (0);
	}
	(*i)++;
	if (tmp == 1)
		string = is_quoted(str, i, 39);
	else
		string = is_double_quoted(str, i);
	(*res) = free_join(*res, string, 0);
	if (!string)
	{
		free(*res);
		return (get_errno(222));
	}
	return (0);
}

// add new pipe or print syntax error
t_pipe	*norm(t_data *data, t_pipe *pipe, char *str)
{
	if ((pipe && !pipe->arg && !(pipe->redirections)->head))
	{
		print_error("syntax error near unexpected token `|'\n", "");
		get_errno(258);
		return (NULL);
	}
	else if (!str[ft_strtrim(str, 0)])
	{
		print_error("unclosed pipe\n", NULL);
		get_errno(222);
		return (NULL);
	}
	return (new_pipe(data, 0));
}

//	parse the input string
short	parse_time(t_data *data, char *str, int i)
{
	int		tmp;
	char	*res;
	t_pipe	*pipe;

	pipe = new_pipe(data, 1);
	res = NULL;
	while (str[i] && pipe)
	{
		i = ft_strtrim(str, i);
		tmp = is_limiter(str + i);
		if (str[i] && (tmp < 3) && (parse_time_2(str, &res, &i, tmp) == 222))
			return (222);
		else if (tmp == 3 && ++i)
			res = new_argument(pipe, split_expand(str, res, &i), res, 1);
		else if (tmp > 5 && ++i && (is_redirection(pipe, str, &i, tmp) == 258))
			return (258);
		if (tmp == 4 || !str[i] || is_limiter(str + i) > 3
			|| str[i] == '\n' || str[i] == '\t')
			res = new_argument(pipe, NULL, res, 0);
		if (tmp == 4 && ++i)
			pipe = norm(data, pipe, str + i);
	}
	return (!pipe);
}
