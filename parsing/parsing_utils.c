/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:38:24 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/17 15:08:15 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_quoted(char *str, int *len, char c)
{
	char	*res;

	res = my_strdup(&str[*len], c);
	(*len) += my_size(NULL, res);
	if (str[*len] != c)
	{
		free (res);
		print_error("unclosed quotes\n", NULL);
		return (NULL);
	}
	(*len)++;
	return (res);
}

char	*error_un(char *str, char *quote_val, int *pos)
{
	if (str[(*pos)++] != 34)
	{
		free (quote_val);
		print_error("unclosed quotes\n", NULL);
		return (NULL);
	}
	return (quote_val);
}

char	*is_double_quoted(char *str, int *pos)
{
	char	*quote_val;
	char	*var;
	int		i;

	quote_val = NULL;
	if ((str[*pos] == 34 && ++(*pos)))
		return (my_strdup("", '\0'));
	while (str[*pos] && str[*pos] != 34)
	{
		i = *pos;
		while (str[*pos] && str[*pos] != 34 && str[*pos] != '$')
			(*pos)++;
		if (str[*pos] == '$' && ++(*pos))
		{
			var = var_expand(str, pos);
			quote_val = free_join(quote_val, my_strdup(&str[i], '$'), 0);
			quote_val = free_join(quote_val, var, 1);
			free (var);
		}
		else
			quote_val = free_join(quote_val, my_strdup(&str[i], str[*pos]), 0);
	}
	return (error_un(str, quote_val, pos));
}
