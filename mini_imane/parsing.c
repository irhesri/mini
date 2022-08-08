/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:48 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/08 13:02:44 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	is_special(char *c)
{
	int			i;
	short		b;
	static char s[10] = "\'\"$| <<>";

	b = 0;
	i = -1;
	while (!b && ++i < 8)
		b = (s[i] == *c) * (i + 1);
	if (b > 4)
		return (b + (*(c + 1) == *c));
	return (b);
}
	
char	*is_quoted(char *str, int *len, char c)
{
	char	*res;
	int		i;

	i = 1;
	res = my_strdup(str + (*len), c);
	(*len) += my_size(NULL, res);
	if (str[*len])
		(*len)++;
	return (res);
}

char	*parse_time_2(char *str, char *res, int *i, int tmp)
{
	if (!tmp)
	{
		tmp = *i;
		while (str[*i] && !is_special(str + *i))
			(*i)++;
		res = free_join(res, my_strdup(str + tmp, str[*i]), 0);
	}
	else if (tmp == 1 && ++(*i))
		res = free_join(res, is_quoted(str, i, 39), 0);
	// else if (tmp == 2)
		// res = free_join(res, is_double_quoted(str + *i + 1, &len), 0);
	// else if (tmp > 5 && ++i)
	// {
	// 	i += (tmp % 2);
	// 	// is_redirection();			
	// }
	return (res);
}

//	EMPTY PIPES.
void	parse_time(t_data *data, char *str)
{
	int		i;
	int		tmp;
	t_pipe	*pipe;
	char	*res;

	i = 0;
	pipe = new_pipe(data, 1);
	res = NULL;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		tmp = is_special(str + i);
		if (tmp < 3 || tmp > 5)
			res = parse_time_2(str, res, &i, tmp);
		else if (tmp == 3 && ++i)
			res = new_argument(pipe, split_expand(str, &i), res);
		if (tmp == 4 || !str[i] || is_special(str + i) > 3)
		{
			res = new_argument(pipe, NULL, res);
			if (tmp == 4 && ++i)
				pipe = new_pipe(data, 0);
		}
	}
}


