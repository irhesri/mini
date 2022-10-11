/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:49:41 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 17:34:33 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	my_exit(char **status)
{
	long long	nb;

	write(1, "exit\n", 5);
	if (status[0] && status[1] && get_errno(1))
	{
		print_error("exit: too many arguments\n", NULL);
		return ;
	}
	if (status[0])
		nb = ft_atoi(status[0]);
	reset_termios_echoctl();
	exit(get_errno(-1));
}
