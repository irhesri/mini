/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:48:26 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/16 17:04:09 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	open_file(char *path)
{

	if (access(path, F_OK) == -1)
		return (127);
	if (is_directory(path))
		return (127);
	if (access(path, X_OK) == -1)
		return (126);
	if (access(path, R_OK) == -1)
		return (125);
	return (1);
}

void	command_error(t_data *data, char *cmd, short b)
{
	char	*str;

	if (b == 1)
		return ;
	if (!data->paths || b == 128)
	{
		if (b == 127 || b == 128)
			print_error(cmd, ": No such file or directory\n");
		else
			print_error(cmd, ": Permission denied\n");
		exit (b + (b == 125) - (b == 128));
	}
	(b == 127) && print_error(cmd, ": command not found\n");
	if (b == 126)
	{
		str = cmd;
		if (my_search(cmd, '/') == -1)
			str = ft_strjoin("./", cmd);
		print_error(str, ": Permission denied\n");
		free (str);
	}
	exit (b + (b == 125));
}

// check if a path or a directory
char	*its_directory_or_path(t_data *data, char *command)
{
	short	b;

	b = my_search(command, '/');
	if (is_directory(command))
	{
		if (data->paths && b == -1)
		{
			print_error(command, ": command not found\n");
			exit (127);
		}
		print_error(command, ": is a directory\n");
		exit (126);
	}
	if (b != -1)
	{
		b = open_file(command);
		(b == 127) && (b = 128);
		command_error(data, command, b);
		return (command);
	}
	return (NULL);
}

char	*get_path(t_data *data, char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*command;
	short	b[2];

	b[0] = 0;
	b[1] = 0;
	i = -1;
	command = ft_strjoin("/", cmd);
	while (paths && paths[++i] && b[0] != 125)
	{
		path = ft_strjoin(paths[i], command);
		b[0] = open_file(path);
		if (b[0] == 1)
			break ;
		b[1] = (b[1] || b[0] == 126 || b[0] == 125);
		free (path);
		path = NULL;
	}
	free (command);
	if (!data->paths)
		paths = free_arr(paths);
	if (b[0] != 1)
		command_error(data, cmd, 127 - b[1]);
	return (path);
}

void	not_builtin(t_data *data, char **arg)
{
	char	*path;
	char	**paths;

	get_errno(0);
	if (arg && *arg)
	{
		path = its_directory_or_path(data, *arg);
		if (!path)
		{
			paths = data->paths;
			if (!paths)
				paths = array_realloc(NULL, my_strdup(".", '\0'), 0);
			path = get_path(data, paths, *arg);
		}
		update_envp(data);
		execve(path, arg, data->envp);
		free(path);
		perror(get_bash_name(NULL));
		exit (errno);
	}
}
