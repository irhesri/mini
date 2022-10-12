/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:34 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/12 22:37:13 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_last(t_pipe *p, int n)
{
	if (!n && p->arg)
		get_last(my_strdup(p->arg[p->n - 1], '\0'), 1);
	else
		get_last(NULL, 1);
}

void	null_exit(void)
{
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	write(1, "exit\n", 5);
	reset_exit (get_errno(-1));
}

void	read_line(t_data *data)
{
	int		n;
	char	*str;

	str = readline("minishell$ ");
	if (!str)
		null_exit();
	n = ft_strtrim(str, 0);
	if (str[n])
	{
		my_add_history(data, str);
		if (!parse_time (data, str, n))
		{
			get_errno(0);
			update_last(data->pipes->head->content, data->nbr_pipes);
			if (!init_files(data))
				run_commands(data, data->pipes);
		}
		else
		{
			init_here_doc(data);
			get_last(NULL, 1);
		}
		empty_pipes(data->pipes);
	}
	free (str);
}

// initialise bash name
// initialise data
// initialise env
// start
int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	get_bash_name("minishell$ ");
	if (ac > 1 || av[1])
		exit(print_error("Too many arguments\n", NULL));
	data = malloc(sizeof(t_data));
	set_termios_echoctl();
	signal(SIGINT, handle_sigint);
	init_data(data);
	init_env(data, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	while (1)
		read_line(data);
	reset_exit(get_errno(-1));
}
