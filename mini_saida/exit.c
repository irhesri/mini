/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:49:41 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 16:03:02 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	my_exit(char **status)
{
	long long	nb;

	
	nb = 0;
	get_errno(0);
	if (status[0] && status[1] && get_errno(1))
	{
		write(1, "exit\n", 5);
		print_error("exit: too many arguments\n", NULL);
		return ;
	}
	if (status[0])
		nb = ft_atoi(status[0]);
	write(1, "exit\n", 5);
	reset_exit(nb);
}
