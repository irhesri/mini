/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:28 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/12 15:03:23 by irhesri          ###   ########.fr       */
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
		exit(printf("allocation error\n"));
	while (*str1)
		res[++i] = *str1++;
	while (*str2)
		res[++i] = *str2++;
	res[++i] = '\0';
	return (res);
}
