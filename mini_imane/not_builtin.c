/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:48:26 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/20 13:14:26 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	open_file(char *path, char *command)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, X_OK) != -1)
		{
			if (access(path, R_OK) != -1)
				return (1);
			command = ft_strjoin("./", command);
			print_error(command, ": Permission denied\n");
			free (command);
			exit (126);
		}
		print_error(command, ": Permission denied\n");
		exit (126);
	}
	return (127);
}

char	*first_check(char *command)
{
	struct stat	file_mode;

	stat(command, &file_mode);
	if (S_ISDIR(file_mode.st_mode)) //check in mac
	{
		print_error(command, ": is a directory\n");
		exit(126);
	}
	if (my_search(command, '/') != -1 && open_file(command, command) == 1)
		return (command);
	return (NULL);
}

char	*check_in_env(char **env_paths, char *command)
{
	char	*path;
	char	**paths;

	paths = env_paths;
	command = ft_strjoin("/", command);
	while (paths && *paths)
	{
		if (**paths)
			path = ft_strjoin(*paths, command);
		else
			path = ft_strjoin(".", command);
		if (open_file(path, command + 1) == 1)
		{
			free (command);
			return (path);
		}	
		free (path);
		paths++;
	}
	free (command);
	return (NULL);
}

char	*get_path(char *command)
{
	char		*path;
	char		**env_paths;

	// path = first_check(command);
	// if (path)
	// 	return (path);
	if (my_search(command, '/') == -1 && *command)
	{
		path = my_getenv("PATH");
		env_paths = my_split(path, ':', 1);
		free(path);
		if (!env_paths && open_file(command, command) == 1)
			return (command);
		path = check_in_env(env_paths, command);
		free_arr(env_paths);
		if (path)
			return (path);
	}
	print_error(command, ": No such file or directory\n");
	exit (127);
}

void	not_builtin(t_data *data, char **arg)
{
	char	*path;

	if (arg && *arg)
	{
		path = get_path(*arg);
		update_envp(data);
		execve(path, arg, data->envp);
		perror("execve");
		exit (errno);
	}
}
