/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:38:24 by sben-chi          #+#    #+#             */
/*   Updated: 2022/08/12 17:01:59 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*is_quoted(char *str, int *len, char c)
{
	char	*res;

	res = my_strdup(&str[*len], c);
	(*len) += my_size(NULL, res);
	if (str[*len])
		(*len)++;
	return (res);
}

char	*is_double_quoted(char *str, int *pos)
{
	char	*quote_val;
	char	*var;
	int		i;

	quote_val = NULL;
	if ((!str[*pos] || str[*pos] == 34) && ++(*pos))
		quote_val = my_strdup("", '\0');
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
		}
		else
			quote_val = free_join(quote_val, my_strdup(&str[i], str[*pos]), 0);
	}
	(str[*pos] == 34) && (*pos)++;
	return (quote_val);
}
