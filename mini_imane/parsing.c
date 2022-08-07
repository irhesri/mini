#include "minishell.h"

short	is_special(char *c)
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
	
char	*is_quoted(char *str, int *len, char c)
{
	char	*res;
	int		i;

	i = 1;
	res = my_strdup(str + (*len), c);
	(*len) += my_size(NULL, res);
	if (str[*len])
		(*len)++;
	return (res);
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

void	var_exist(char *str, int *pos)
{
	while (str[*pos] && str[*pos] != 34 && str[*pos] != '$')
		(*pos)++;
}

char *is_double_quoted(char *str, int *size)
{
	char	*quote_val;
	char	*var;
	int		pos;
	int		i;

	pos = 0;
	quote_val = NULL;
	while (str[pos] && str[pos] != 34)
	{
		i = pos;
		var_exist(str, &pos);
		if (str[pos] == '$')
		{
			var = var_expand(str + pos, size);
			quote_val = free_join(quote_val, my_strdup(&str[i], str[pos]), 0);
			quote_val = free_join(quote_val, var, 1);
			pos += *size;
		}
		else
			quote_val = free_join(quote_val, my_strdup(&str[i], str[pos]), 0);
	}
	*size = pos + 1;
	if (str[*size])
		(*size)++;
	return (quote_val);
}

void	parse_functions_call()
{
	
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
		tmp = is_special(str + i);
		if (!tmp)
		{
			tmp = i;
			while (str[i] && !is_special(str + i))
				i++;
			res = free_join(res, my_strdup(str + tmp, str[i]), 0);
		}
		else if (tmp == 1 && ++i)
			res = free_join(res, is_quoted(str, &i, 39), 0);
		// else if (tmp == 2)
			// res = free_join(res, is_double_quoted(str + i + 1, &len), 0);
		else if (tmp == 3 && ++i)
			res = new_argument(pipe, split_expand(str, &i), res);
		else if (tmp == 4 && ++i)
		{
			res = new_argument(pipe, NULL, res);
			pipe = new_pipe(data, 0);
			continue;
		}
		else if (tmp > 5 && ++i)
		{
			i += (tmp % 2);
			// is_redirection();			
		}
		if (!str[i] || is_special(str + i) > 3)
			res = new_argument(pipe, NULL, res);
	}
}



// is_redirection(t_list *input, t_list *output, t_list *env, short type)