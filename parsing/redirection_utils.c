/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:26:44 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 18:46:10 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	is_special_red(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == ';');
}

char	*normal_chars(char *str, int *i, short b)
{
	int	j;

	j = *i;
	while (str[*i] && !is_special_red(str[*i])
		&& str[*i] != 39 && str[*i] != 34)
	{
		if (!b && str[*i] == '$')
			break ;
		(*i)++;
	}
	return (my_strdup(&str[j], str[(*i)]));
}
