/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:56:37 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 16:03:10 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	char				*temp;

	nb = 0;
	sign = 1;
	temp = str;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	str += (*str == '+' || *str == '-');
	while (*str >= 48 && *str <= 57 && nb < 9223372036854775809ull)
		nb = (nb * 10) + (*(str++) - 48);
	if ((*str && *str != ' ') || (nb > 9223372036854775807ull && sign > 0)
		|| (sign < 0 && nb > 9223372036854775808ull))
	{
		printf("exit\nsben-chi: exit: %s: numeric argument required\n", temp);
		reset_exit(255);
	}
	return ((long long)nb * sign);
}
