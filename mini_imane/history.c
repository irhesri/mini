/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:34:04 by imane             #+#    #+#             */
/*   Updated: 2022/10/08 01:02:51 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_add_history(t_data *data, char *str)
{
	add_history(str);
	str = free_join(free_join(ft_itoa(++data->history_lines), "  ", 1),
			ft_strjoin(str, "\n"), 0);
	data->history_size += my_size(NULL, str);
	data->history = array_realloc(data->history, str, -1);
}

short	display_history(t_data *data)
{
	static int	i;
	static char	*j_history;

	if (!data)
	{
		free(j_history);
		return (1);
	}
	if (!data->history)
		return (1);
	if (!i)
		j_history = my_strdup(data->history[i++], '\0');
	while (i < data->history_lines)
		j_history = free_join(j_history, data->history[i++], 1);
	write(STDOUT_FILENO, j_history, data->history_size);
	return (1);
}

void	display_some_history(t_data *data, int n)
{
	int		i;
	int		size;
	char	*str;
	char	**history;

	i = 0;
	size = 0;
	str = NULL;
	history = data->history;
	str = my_strdup(history[data->history_lines - 1], '\0');
	while (++i < n)
		str = free_join(history[data->history_lines - i - 1], str, 2);
	write(STDOUT_FILENO, str, my_size(NULL, str));
	free (str);
}

void	history(t_data *data, char **arg)
{
	char		*str;
	long long	n;

	if ((!arg || !*arg) && display_history(data))
		return ;
	n = my_atoi(*arg);
	if (n < 0 && get_errno(n * -1))
	{
		str = ft_strjoin("history: ", *arg);
		(n == -1) && print_error(str, ": numeric argument required\n");
		(n == -2) && print_error(str, ": invalid option\n");
		free(str);
		return ;
	}
	if (*(arg + 1) && get_errno(1))
	{
		print_error("history: too many arguments\n", NULL);
		return ;
	}
	if (!(n >= data->history_lines && display_history(data)) && n > 0)
		display_some_history(data, n);
}
