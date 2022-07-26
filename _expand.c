#include "minishell.h"

static int	is_special(char c)
{		
	return (!((c > 47 && c < 58) || (c > 64 && c < 91)
			|| (c > 96 && c < 123) || (c == 95)));
}

char	*get_var_data(t_node *node)
{
	int		i;
	char	*str;

	str = NULL;
	if (node)
	{
		str = node->str;
		i = my_search(str, '=');
		str = my_strdup(str + i + 1, '\0');
	}
	return (str);
}

char	*var_expand(t_list *env, char *str, int *len)
{
	int		i;
	char	c;
	char	*res;
	t_node	*node;

	(*len) = 0;
	res = str;
	if (str[(*len)] > 47 && str[(*len)] < 58)
	{
		c = str[++(*len)];
		str[(*len)] = '\0';
		str = my_strdup(str, '\0');
		res[(*len)] = c;
		return (my_strjoin("$", str));
	}
	while (!is_special(str[(*len)]) && str[(*len)])
		(*len)++;
	if (!(*len))
		return (my_strdup("$", '\0'));
	c = str[(*len)];
	str[(*len)] = '\0';
	node = my_getenv(env->head, str);
	str = get_var_data(node);
	res[(*len)] = c;
	return (str);
}
