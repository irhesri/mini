#include "minishell.h"

// expand one variable only without joining
char	*var_expand(char *str, int *size)
{
	int		i;
	char	c;
	char	*res;
	t_node	*node;

	res = str;
	(*size) = 1;
	if (is_digit(str[(*size)]) || str[*size] == '$')
	{
		c = str[++(*size)];
		str[(*size)] = '\0';
		str = my_strdup(str, '\0');
		res[(*size)] = c;
		return (str);
	}
	while (str[(*size)] && (is_digit(str[(*size)]) || is_alphabet(str[(*size)]) || str[(*size)] == '_'))
		(*size)++;
	if ((*size) == 1 && !str[(*size)])
		return (my_strdup("$", '\0'));
	if ((*size) == 2 && str[(*size) - 1] == '_')
		return (my_strdup(get_last(NULL, 0), '\0'));
	else if ((*size) == 1)
		return (NULL);
	c = str[(*size)];
	str[(*size)] = '\0';
	str = my_getenv(str + 1);
	res[(*size)] = c;
	return (str);
}

// expand
// split if b == 1
char	**split_expand(char *str, int *len)
{
	char	**ress;
	char	*res;

	// if (str[1] == 39 || str[1] == '"')
	// 	return (is_double_quoted());
	res = var_expand(str, len);
	ress = my_split(res, ' ', 0);
	free (res);
	return (ress);
}