#include "../mini_imane/minishell.h"

short	is_special(char *c)
{
	int			i;
	short		b;
	static char s[10] = "\'\"$| <<>";

	// if (*c == 39)
	// 	return (1);
	// if (*c == 34)
	// 	return (2);
	// if (*c == '$')
	// 	return (3);
	// if (*c == '|')
	// 	return (4);
	// if (*c == ' ')
	// 	return (5);
	// if (*c == '<')
	// 	return (6 + (*(c + 1) == '<'));
	// if (*c == '>')
	// 	return (8 + (*(c + 1) == '>'));
	b = 0;
	i = -1;
	while (!b && ++i < 8)
		b = (s[i] == *c) * (i + 1);
	if (b > 4)
		return (b + (*(c + 1) == *c));
	return (b);
}
	
// char	*is_quoted(t_pipe *pipe, char *str, int *len)
// {
// 	char	*res;
// 	int		i;

// 	i = 1;
// 	res = my_strdup(str, 39);
// 	(*len) = my_size(NULL, res) + 1;
// 	if (str[*len])
// 		(*len)++;
// 	return (res);
// }


t_pipe	*new_pipe(t_data *data, short b)
{
	t_pipe		*pipe;
	static int	id;

	if (b)
		id = 0;
	pipe = malloc(sizeof(t_pipe));
	pipe->pipe_id = id++;
	pipe->arg = NULL;
	pipe->n = 0;
	pipe->input = malloc(sizeof(t_list));
	(pipe->input)->head = NULL;
	pipe->output = malloc(sizeof(t_list));
	(pipe->output)->head = NULL;
	add_node(data->pipes, (data->pipes)->last, pipe);
	data->nbr_pipes = id + 1;
	return (pipe);
}

char	*new_argument(t_data *data, t_pipe *pipe, char **res2, char *res)
{
	char	**tmp;

	if (res2)
	{
		tmp = res2;
		res = free_join(res, *res2, 0);
		while (*res2 && *(res2 + 1))
		{
			pipe->n++;
			pipe->arg = array_realloc(pipe->arg, res, -1);
			res = *(++res2);
		}
		free (tmp);
	}
	else if (res)
	{
		if (res && !*res)
		{
			free (res);
			return (NULL);
		}
		pipe->arg = array_realloc(pipe->arg, res, -1);
		pipe->n++;
		if (pipe->pipe_id == 0 && res)
			get_last(my_strdup(res, '\0'), 1);
		else
			get_last(NULL, 1);
		res = NULL;
	}
	return (res);
}


//	EMPTY PIPES.
void	parse_time(t_data *data, char *str)
{
	int		i;
	int		len;
	int		tmp;
	t_pipe	*pipe;
	char	*res;

	i = 0;
	pipe = new_pipe(data, 1);
	res = NULL;
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
		}
		else if (tmp == 1)
			res = free_join(res, is_quoted(str + i + 1, &len, 39), 0);
		else if (tmp == 2)
		 	res = free_join(res, is_double_quoted(str + i + 1, &len), 0);
		else if (tmp == 3)
			res = new_argument(data, pipe, split_expand(str + i, &len), res);
		else if (tmp == 4)
		{
			res = new_argument(data, pipe, NULL, res);
			pipe = new_pipe(data, 0);
			i++;
			continue ;
		}
		else if (tmp > 5)
		{
		 	len += (is_redirection(pipe->input, pipe->output, str + i + 1 + (tmp % 2), tmp) );
			printf("tmp ===> %d\n", tmp);
		}
		i += len;
		if (!str[i] || is_special(str + i) > 3)
			res = new_argument(data, pipe, NULL, res);
	}
	printf("res => %s\n", res);
}



// is_redirection(t_list *input, t_list *output, t_list *env, short type)
