/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:09:53 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/20 12:55:25 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_arg(t_data *data, char **arg)
{
	while (arg && *arg)
	{
		printf("%s\n", *arg);
		arg++;
	}
}

short	is_builtin(char *arg)
{
	short		i;
	short		b;
	static char	*call[8] = {"export", "unset", "exit", "cd",
		"env", "echo", "pwd"};
	
	i = -1;
	b = 0;
	while (arg && !b && ++i < 8)
		b = !ft_strncmp(call[i], arg, 10) * (i + 1);
	return (b);
}

void	commands_call(t_data *data, char **arg)
{
	short		b;
	static void	(*ptr[8])();


	if (!ptr[0])
	{
		ptr[0] = not_builtin;
		ptr[1] = export;
		ptr[2] = unset;
		ptr[3] = exit;
		ptr[4] = cd;
		ptr[5] = env;
		ptr[6] = echo;
		ptr[7] = pwd;
	}
	b = is_builtin(*arg);
	if (b < 5 && arg)
		ptr[b](data, arg + (b != 0));
	else
		ptr[b](arg + 1);
}
