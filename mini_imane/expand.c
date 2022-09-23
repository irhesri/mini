/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:09 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/23 22:19:42 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// get enviroment variable data
char	*my_getenv(char *str)
{
	int		i;
	t_list	*env;
	t_node	*node;

	env = get_env(NULL);
	node = getenv_node(env->head, str);
	if (!node)
		return (NULL);
	str = (char *)node->content;
	i = my_search(str, '=');
	str = my_strdup(str + i + 1, '\0');
	return (str);
}

static char	*special_cases(char *str, int *size)
{
	char	*res;

	if (is_digit(str[(*size)]) || str[*size] == '$')
	{
		res = malloc(2);
		res[0] = str[(*size)++];
		res[1] = '\0';
		str = free_join("$", res, 2);
		return (str);
	}
	if (str[(*size)] == '?' && ++(*size))
		return (ft_itoa(get_errno(-1)));
	if (is_limiter(str + (*size)))
		return (my_strdup("$", '\0'));
	return (NULL);
}

// expand variable without splitting
char	*var_expand(char *str, int *size)
{
	char	c;
	char	*res;

	res = special_cases(str, size);
	if (res)
		return (res);
	res = str + (*size);
	while (str[(*size)] && (is_alphanum(str[(*size)]) || str[(*size)] == '_'))
		(*size)++;
	c = str[(*size)];
	str[(*size)] = '\0';
	if (!ft_strncmp(res, "_", 2))
		res = my_strdup(get_last(NULL, 0), '\0');
	else
		res = my_getenv(res);
	str[(*size)] = c;
	return (res);
}

// expand and split
char	**split_expand(char *str, int *len)
{
	char	**ress;
	char	*res;

	res = var_expand(str, len);
	str = res;
	while (str && *str)
	{
		if (*str == '\t' || *str == '\n')
			*str = ' ';
		str++;
	}
	ress = my_split(res, ' ', 0);
	free (res);
	return (ress);
}
