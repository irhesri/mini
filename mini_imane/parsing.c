#include "minishell.h"

short	is_special(char *c)
{
	if (*c == 39)
		return (1);
	if (*c == 34)
		return (2);
	if (*c == '$')
		return (3);
	if (*c == '|')
		return (4);
	if (*c == ' ')
		return (5);
	if (*c == '<')
		return (6 + (*(c + 1) == '<'));
	if (*c == '>')
		return (8 + (*(c + 1) == '>'));
	return (0);
}
	
char	*is_quoted(t_pipe *pipe, char *str, int *len)
{
	char	*res;
	int		i;

	i = 1;
	res = my_strdup(str, 39);
	(*len) = my_size(NULL, res) + 1;
	if (str[*len])
		(*len)++;
	return (res);
}


t_pipe	*new_pipe(t_data *data)
{
	t_pipe		*pipe;
	static int	id;

	pipe = malloc(sizeof(t_pipe));
	pipe->pipe_id = id++;
	pipe->arg = NULL;
	pipe->last_arg = NULL;
	pipe->n = 0;
	add_node(data->pipes, (data->pipes)->last, pipe);
	return (pipe);
}

void	parse_time(t_data *data, char *str)
{
	int		i;
	int		len;
	int		tmp;
	t_pipe	*pipe;
	char	*res;
	char	**res2;

	i = 0;
	pipe = new_pipe(data);
	res = NULL;
	res2 = NULL;
	while (str[i])
	{
		len = 0;
		while (str[i] == ' ')
			i++;
		tmp = is_special(str + i);
		if (!tmp)
		{
			tmp = i;
			while (str[i] && !is_special(str + i))
				i++;
			res = free_join(res, my_strdup(str + tmp, str[i]), 0);
			tmp = -1;
		}
		else if (tmp == 1)
			res = free_join(res, is_quoted(pipe, str + i + 1, &len), 0);
		// else if (tmp == 2)
		// 	res2 = is_double_quoted();
		else if (tmp == 3)
			res2 = expand(data->env, str + i, &len, 0);
		else if (tmp == 4)
		{
			// pipe->arg = array_realloc(pipe->arg, res, -1);
			// pipe->last_arg = res;
			// pipe->n++;
			// res = NULL;
			pipe = new_pipe(data);
		}
		// else if (tmp > 5)
		// 	len += (is_redirection() + 1 + (tmp % 2));
		i += len;
		if (res2)
		{
			*res2 = free_join(res, *res2, 0);
			while (*(res2 + 1))
				array_realloc(pipe->arg, *res2++, -1);
			res = *res2;
			free(res2);
		}
		if (!str[i] || is_special(str + i) > 3)
		{
			// printf("%s\n", res)
			pipe->arg = array_realloc(pipe->arg, res, -1);
			pipe->last_arg = res;
			pipe->n++;
			res = NULL;
		}
	}
	
}

void	init_data(t_data *data, char *str)
{
	data->red = malloc(sizeof(t_list));
	(data->red)->head = NULL;
	(data->red)->last = NULL;
	data->pipes = malloc(sizeof(t_list));
	(data->pipes)->head = NULL;
	(data->pipes)->last = NULL;
	(data->pipes)->last = NULL;
	parse_time (data, str);
}