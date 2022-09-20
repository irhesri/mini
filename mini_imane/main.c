/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:34 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/20 11:52:12 by imane            ###   ########.fr       */
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
	get_bash_name("our_bash");
	while (1)
	{
		str = readline("---->  ");
		add_history(str);
		if (!*str)
		{
			free (str);
			continue ;
		}
		if (!str)
			exit (0);
		parse_time (data, str);
		init_files(data);
		// print_pipes(data, data->pipes);
		// commands_call(data, ((t_pipe *)(((data->pipes)->head)->content))->arg);
		run_commands(data, data->pipes);
		// red_test(data->pipes);
		empty_pipes(data->pipes);
		free (str);
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

