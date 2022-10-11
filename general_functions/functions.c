/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:16 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/07 23:51:15 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns arr size if str NULL
// returns str size if arr NULL
// returns 0 if both of them NULL
// returns str size + arr size if both of them !NULL
size_t	my_size(char **arr, char *str)
{
	size_t	size;

	size = 0;
	while (str && str[size])
		size++;
	while (arr && arr[size])
		size++;
	return (size);
}

// returns substring of str from the beginning to char c 
// c not included
// returns copy of str if c doesn't exist
char	*my_strdup(char *str, char c)
{
	int		i;
	int		size;
	char	*new;

	if (!str)
		return (str);
	size = -1;
	if (c != '\0')
		size = my_search(str, c);
	if (size == -1)
		size = my_size(NULL, str);
	new = malloc(size + 1);
	i = -1;
	while (str[++i] && str[i] != c)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

//	returns c index in str
//	returns -1 if c doesn't exist
int	my_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
}

// does dup2 work
// close *newfd
// assign -1 to *newfd
int	my_dup2(int *newfd, int oldfd)
{
	if (*newfd < 0)
		return (-1);
	if (dup2(*newfd, oldfd) == -1)
		return (-1);
	close(*newfd);
	(*newfd) = -1;
	return (1);
}

char	*ft_itoa(int n)
{
	int		tmp;
	int		size;
	char	*str;

	tmp = n;
	size = 0;
	while (!size || tmp)
	{
		size++;
		tmp /= 10;
	}
	str = malloc(size + 1);
	str[size] = '\0';
	while (--size >= 0)
	{
		str[size] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}
