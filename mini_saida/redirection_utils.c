/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:26:44 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/10 14:55:19 by sben-chi         ###   ########.fr       */
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

void	ft_error(char *str, char **name, int *i)
{
	*name = free_join(*name, normal_chars(str, i, 1), 0);
	print_error(*name, ": ambiguous redirect\n");
	free(*name);
	*name = NULL;
}
