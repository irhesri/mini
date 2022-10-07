/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:34 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/28 17:40:16 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_data *data;

	data = malloc(sizeof(t_data));
	init_data(data);
	init_env(data, envp);
	// get_env(data->env);
	while (1)
	{
		str = readline("---->  ");
		add_history(str);
		if (!*str)
			continue ;
		if (!str)
			exit (0);
		parse_time (data, str);
		print_pipes(data, data->pipes);
		free (str);
		commands_call(data, ((t_pipe *)(((data->pipes)->head)->content))->arg);
		empty_pipes(data->pipes);
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*str;
// 	t_data *data;

// 	data = malloc(sizeof(t_data));
// 	init_data(data);
// 	init_env(data, envp);
// 	// free_all(data);
// 	// print_list(get_env(NULL));
// 	export (data, NULL);
// }

