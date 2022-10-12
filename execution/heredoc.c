/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:00:03 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 18:48:22 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	chr_rp_var(char *line, int fd)
{
	int		i;
	char	*var;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			var = var_expand(line, &i);
			write(fd, var, my_size(NULL, var));
			free(var);
		}
		else
			write(fd, &line[i], 1);
	}
	return (1);
}

void	my_wait(void)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WTERMSIG(status) && WIFSIGNALED(status))
	{
		get_errno(1);
		write(1, "\n", 1);
	}
	signal(SIGINT, handle_sigint);
}

short	heredoc(int fd, t_redirection *red)
{
	char	*line;
	int		len;

	get_errno(0);
	if (!fork())
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			len = my_size(NULL, line);
			if (!line || !ft_strncmp(line, red->name, len + 1))
				break ;
			red->fd == -2 && chr_rp_var(line, fd);
			red->fd == -3 && write(fd, line, len);
			write(fd, "\n", 1);
			free(line);
			line = NULL;
		}
		close(fd);
		exit(0);
	}
	my_wait();
	return (get_errno(-1));
}