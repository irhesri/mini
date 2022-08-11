/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:48:26 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/11 17:51:12 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	open_file(char *path, char *command)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, X_OK) != -1 && access(path, R_OK) != -1)
			return (1);
		// bash: command: Permission denied
		exit (126);
	}
	return (127);
}

char	*first_check(char *command)
{
	struct stat	file_mode;
	
	stat(command, &file_mode);
	if (file_mode.st_mode == S_IFDIR)
	{
		// bash: command: is a directory
		exit(126);
	}
	if (my_search(command, '/') != -1 && open_file(command, command) == 1)
		return (command);
	return (NULL);
}

char	*get_path(char *command)
{
	char		*path;
	char		**env_paths;

	path = first_check(command);
	if (path)
		return (path);
	if (my_search(command, '/') == -1 && *command)
	{
		path = my_getenv(command);
		env_paths = my_split(path, ':', 1);
		free(path);
		if (!env_paths && open_file(command, command) == 1)
			return (command);
		while (env_paths && *env_paths)
		{
			path = free_join(*env_paths, command, 1);
			// add / to the join
			if (open_file(path, *command) == 1)
			{
				while (*(++env_paths))
					free (*env_paths);
				free(env_paths);
				return (path);
			}
		}
		free(env_paths);
	}
	// bash: command: No such file or directory
	exit (127);
}

void	not_builtin(t_data *data, char **arg)
{
	char	*path;

	path = get_path(*arg);
	update_envp(data);
	execve(path, arg, data->envp);
	perror(*arg);
}