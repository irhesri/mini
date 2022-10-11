/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:53:26 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 11:46:47 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	check_option(char **str, int *option)
{
	int	j;
	int	i;

	i = -1;
	while (str[++i] && str[i][0] == '-')
	{
		j = 1;
		while (str[i][j] && str[i][j] == 'n')
			j++;
	}
	*option = ((i > 0 && !str[i - 1][j] && j > 1) || i > 1);
	if (i && (str[i - 1][j] || j == 1))
		i--;
	return (i);
}

void	echo(char **towrite)
{
	int	i;
	int	option;

	option = 0;
	i = check_option(towrite, &option);
	get_errno(0);
	while (towrite[i])
	{
		write(1, towrite[i], my_size(NULL, towrite[i]));
		if (towrite[++i])
			write(1, " ", 1);
	}
	!option && write(1, "\n", 1);
}
