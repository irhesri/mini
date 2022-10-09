/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:34 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/09 18:13:02 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_last(t_pipe *p, int n)
{
	if (!n)
		get_last(my_strdup(p->arg[p->n - 1], '\0'), 1);
	else
		get_last(NULL, 1);
}

void	read_line(t_data *data)
{
	char	*str;

	str = readline("---->  ");
	if (!str)
		free_exit (data, get_errno(-1));
	if (!*str)
	{
		free (str);
		return ;
	}
	my_add_history(data, str);
	if (!parse_time (data, str))
	{
		get_errno(0);
		update_last(data->pipes->head->content, data->nbr_pipes);
		if (!init_files(data))
			run_commands(data, data->pipes);
	}
	else
	{
		get_errno(1);
		get_last(NULL, 1);
	}
	empty_pipes(data->pipes);
	free (str);
}

// initialise bash name
// initialise data
// initialise env
// initialise data in free exit
// start
int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	get_bash_name("our_bash");
	if (ac > 1 || av[1])
		exit(print_error("Too many arguments\n", NULL));
	data = malloc(sizeof(t_data));
	init_data(data);
	init_env(data, envp);
	free_exit(data, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	rl_clear_history();
	while (1)
		read_line(data);
	free_exit(data, get_errno(-1));
	return (0);
}
