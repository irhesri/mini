/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:49:48 by imane             #+#    #+#             */
/*   Updated: 2022/09/20 12:50:24 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(get_bash_name(NULL), ": ");
	str1 = ft_strjoin(str1, str2);
	str = free_join(str, str1, 0);
	ft_putstr(str);
	free (str);
}
