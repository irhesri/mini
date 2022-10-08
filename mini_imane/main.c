/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:34 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/08 11:15:27 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_line(t_data *data)
{
	char	*str;
	
	while (1)
	{
		str = readline("---->  ");
		if (!*str)
		{
			free (str);
			continue;
		}
		if (!str)
			free_exit (data, get_errno(-1));
		my_add_history(data, str);
		if (!parse_time (data, str))
		{
			get_errno(0);
			init_files(data);
			run_commands(data, data->pipes);
		}
		else
			get_errno(1);
		empty_pipes(data->pipes);
		free (str);
	}

}

void	sig_handler(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_data *data;
	char *str;

	data = malloc(sizeof(t_data));
	// initialise data
	init_data(data);
	// initialise env
	init_env(data, envp);
	//initialise bash name
	get_bash_name("our_bash");
	// initialise data in free exit
	free_exit(data, 0);
	// start

	 
	rl_clear_history();
	read_line(data);
	free_exit(data, get_errno(-1));
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

