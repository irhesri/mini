/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:09:53 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/12 11:54:22 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	print_arg(char **arg)
{
	while (arg && *arg)
	{
		printf("%s\n", *arg);
		arg++;
	}
	
}
void	commands_call(t_data *data, char **arg)
{
	int			i;
	short		b;
	static void	(*ptr[8])();
	static char	*call[10] = {"export", "unset", "exit", "cd", "env", "echo", "pwd"};

	if (!ptr[0])
	{
		ptr[0] = not_builtin;
		ptr[1] = export;
		ptr[2] = unset;
		// ptr[3] = exit;
		// ptr[4] = cd;
		ptr[5] = env;
		// ptr[6] = echo;
		// ptr[7] = pwd;
	}
	b = 0;
	i = -1;
	while (!b && arg && ++i < 8)
		b = !ft_strncmp(call[i], *arg, 10) * (i + 1);
	if (b < 5 && arg)
		ptr[b](data, arg + (b != 0));
	else
		ptr[b](arg + 1);
}