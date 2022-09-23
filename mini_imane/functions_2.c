/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:49:48 by imane             #+#    #+#             */
/*   Updated: 2022/09/23 23:34:35 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// bash name: str1str2
void	print_error(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(get_bash_name(NULL), ": ");
	str1 = ft_strjoin(str1, str2);
	str = free_join(str, str1, 0);
	ft_putstr(str);
	free (str);
}

// b == 0 add str in the beginning of arr
// b == -1 add str in the end of arr
// i free arr
char	**array_realloc(char **arr, char *str, short b)
{
	char	**res;
	size_t	size;
	int		i;
	int		j;

	if (!str)
		return (arr);
	size = my_size(arr, NULL) + 2;
	res = malloc(sizeof(char *) * (size + 1));
	i = b;
	j = -1;
	while (arr && arr[++j])
		res[++i] = arr[j];
	i += (b == -1);
	res[i * (b != 0) + b * (b == 0)] = str;
	res[++i] = NULL;
	free (arr);
	return (res);
}

// b == 1 : free(str1)
// b == 2 : free(str2)
// b == 0 : free both
char	*free_join(char *str1, char *str2, short b)
{
	char	*str;

	if (!str2)
		return (str1);
	if (!str1)
		return (str2);
	str = ft_strjoin(str1, str2);
	if (!b || b == 1)
		free (str1);
	if (!b || b == 2)
		free (str2);
	return (str);
}
