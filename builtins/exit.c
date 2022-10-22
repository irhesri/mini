/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:49:41 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/22 18:14:14 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	my_exit(t_data *data, char **status)
{
	long long	nb;

	if (data->nbr_pipes == 0)
		write(1, "exit\n", 5);
	if (status[0] && status[1] && get_errno(1))
	{
		print_error("exit: too many arguments\n", NULL);
		return ;
	}
	nb = get_errno(-1);
	if (status[0])
		nb = ft_atoi(status[0]) % 256;
	if (nb < 0)
		nb += 256;
	reset_exit(get_errno(nb));
}
