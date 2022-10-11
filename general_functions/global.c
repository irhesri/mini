/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:21 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/10 18:27:13 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_env(t_list *env)
{
	static t_list	*g_env;

	if (!g_env)
		g_env = env;
	return (g_env);
}

t_list	*get_exp(t_list *exp)
{
	static t_list	*g_exp;

	if (!g_exp)
		g_exp = exp;
	return (g_exp);
}

char	*get_last(char *last, int b)
{
	static char	*g_last;

	if (b)
	{
		free (g_last);
		g_last = last;
	}
	return (g_last);
}

char	*get_bash_name(char *str)
{
	static char	*name;

	if (!name && str)
		name = str;
	return (name);
}

int	get_errno(int n)
{
	static int	error;

	if (n >= 0)
		error = n;
	return (error);
}
