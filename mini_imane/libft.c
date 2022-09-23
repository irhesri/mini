/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:28 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/23 21:04:15 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	if (!str1 || !str2)
		return (1);
	while (--n && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

// doesn't free
char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(my_size(NULL, str1) + my_size(NULL, str2) + 1);
	if (!res)
		exit(ft_putstr("allocation error\n"));
	while (*str1)
		res[++i] = *str1++;
	while (*str2)
		res[++i] = *str2++;
	res[++i] = '\0';
	return (res);
}

short	ft_putstr(char *str)
{
	write(1, str, my_size(NULL, str));
	return (1);
}
