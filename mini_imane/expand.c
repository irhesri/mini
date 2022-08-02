#include "minishell.h"

// expand one variable only without joining
char	*var_expand(t_list *env, char *str, int *size)
{
	int		i;
	char	c;
	char	tmp;
	char	*res;
	t_node	*node;

	res = str;
	if (str[(*size)] > 47 && str[(*size)] < 58)
	{
		c = str[++(*size)];
		str[(*size)] = '\0';
		str = my_strdup(str, '\0');
		res[(*size)] = c;
		return (ft_strjoin("$", str));
	}
	tmp = str[(*size)];
	while (!(is_digit(tmp) || is_alphabet(tmp) || tmp == '_') && str[(*size)])
		(*size)++;
	if (!(*size))
		return (my_strdup("$", '\0'));
	c = str[(*size)];
	str[(*size)] = '\0';
	str = my_getenv(env, str);
	res[(*size)] = c;
	return (str);
}

// expand and join variables
char	*_expand(t_list *env, char *str, int *len)
{
	int		size;
	char	*res;

	size = 1;
	(*len) = 0;
	res = NULL;
	while (*(str + *len) == '$')
	{
		size = 0;
		res = free_join(res, var_expand(env, str + (*len) + 1, &size), 0);
		(*len) += size + 1;
		size = 0;
		while (*(str + *len + size) != ' ' && *(str + *len + size) != '|'
			&& *(str + *len + size) != '$' && *(str + *len + size) != '"'
			&& *(str + *len + size) != '\0')
			size++;
		if (size)
			res = free_join(res, \
				my_strdup(str + *len, *(str + *len + size)), 0);
		(*len) += size;
	}
	return (res);
}

// expand
// split if b == 1
char	**expand(t_list *env, char *str, int *len, short b)
{
	char	*res;
	char	**ress;

	res = _expand(env, str, len);
	if (b)
	{
		ress = my_split(res, ' ', 0);
		free (res);
	}
	else
		ress = array_realloc(NULL, res, 0);
	return (ress);
}