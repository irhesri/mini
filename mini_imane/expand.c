/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:09 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/08 13:02:44 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// expand variable without splitting
char	*var_expand(char *str, int *size)
{
	char	c;
	char	*res;

	res = str + (*size);
	if (is_digit(str[(*size)]) || str[*size] == '$')
	{
		str = free_join("$", my_strdup(str + (*size), str[(*size)]), 2);
		return (str);
	}
	if (!str[(*size)])
		return (my_strdup("$", '\0'));
	while (str[(*size)] && (is_digit(str[(*size)]) || is_alphabet(str[(*size)]) || str[(*size)] == '_'))
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
	while (*str)
	{
		if (*str == '\t' || *str == '\n')
			*str = ' ';
		str++;
	}
	ress = my_split(res, ' ', 0);
	free (res);
	return (ress);
}