#include "minishell.h"

// expand one variable only without joining
char	*var_expand(t_list *env, char *str, int *size)
{
	int		i;
	char	c;
	char	*tmp;
	t_node	*node;

	tmp = str;
	(*size) = 1;
	if (is_digit(str[(*size)]))
	{
		c = str[++(*size)];
		str[(*size)] = '\0';
		str = my_strdup(str, '\0');
		tmp[(*size)] = c;
		return (ft_strjoin("$", str));
	}
	while (str[(*size)] && (is_digit(str[(*size)]) || is_alphabet(str[(*size)]) || str[(*size)] == '_'))
		(*size)++;
	if ((*size) == 1)
		return (NULL);
	c = str[(*size)];
	str[(*size)] = '\0';
	str = my_getenv(env, str + 1);
	tmp[(*size)] = c;
	return (str);
}

// expand and join variables
// char	*_expand(t_list *env, char *str, int *len)
// {
// 	int		size;
// 	char	*res;

// 	size = 1;
// 	(*len) = 0;
// 	res = NULL;
// 	while (*(str + *len) == '$')
// 	{
// 		size = 0;
// 		res = free_join(res, var_expand(env, str + (*len) + 1, &size), 0);
// 		(*len) += size + 1;
// 		size = 0;
// 		while (*(str + *len + size) != ' ' && *(str + *len + size) != '|'
// 			&& *(str + *len + size) != '$' && *(str + *len + size) != '"'
// 			&& *(str + *len + size) != '\0')
// 			size++;
// 		if (size)
// 			res = free_join(res, \
// 				my_strdup(str + *len, *(str + *len + size)), 0);
// 		(*len) += size;
// 	}

// 	return (res);
// }

// expand
// split if b == 1
char	**split_expand(t_list *env, char *str, int *len)
{
	char	**ress;
	char	*res;

	// if (str[1] == 39 || str[1] == '"')
	// 	return (is_double_quoted());
	res = var_expand(env, str, len);
	ress = my_split(res, ' ', 0);
	if (res)
		free (res);
	return (ress);
}
