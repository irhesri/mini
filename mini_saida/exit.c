/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:49:41 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/10 16:04:03 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	my_exit(char **status)
{
	long long	nb;

	get_errno(0);
	if (!status[0])
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	nb = ft_atoi(status[0]);
	if (status[1] && get_errno(1))
	{
		print_error("exit\n", "sben-chi: exit: too many arguments\n");
		return ;
	}
	write(1, "exit\n", 5);
	exit(nb);
}
