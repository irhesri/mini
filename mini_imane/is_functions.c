/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:39:35 by imane             #+#    #+#             */
/*   Updated: 2022/10/10 16:00:55 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

short	is_alphanum(char c)
{
	return (is_digit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

short	is_builtin(char *arg)
{
	short		i;
	short		b;
	static char	*call[9] = {"export", "unset", "history", "cd",
		"exit", "env", "echo", "pwd"};

	i = -1;
	b = 0;
	while (arg && !b && ++i < 9)
		b = !ft_strncmp(call[i], arg, 10) * (i + 1);
	return (b);
}

short	is_limiter(char *c)
{
	int			i;
	short		b;
	static char	s[10] = "\'\"$| <<>";

	if (*c == '\0')
		return (-1);
	b = 0;
	i = -1;
	while (!b && ++i < 8)
		b = (s[i] == *c) * (i + 1);
	if (b > 4)
		return (b + (*(c + 1) == *c));
	return (b);
}
