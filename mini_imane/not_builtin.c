/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:48:26 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/13 12:30:49 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// short	open_file(char *path, char *command)
// {
// 	if (access(path, F_OK) != -1)
// 	{
// 		if (access(path, X_OK) != -1)
// 		{
// 			if (access(path, R_OK) != -1)
// 				return (1);
// 			// bash: ./command: Permission denied
// 			exit (126);
// 		}
// 		// bash: command: Permission denied
// 		exit (126);
// 	}
// 	return (127);
// }

// char	*first_check(char *command)
// {
// 	struct stat	file_mode;
	
// 	stat(command, &file_mode);
// 	if (file_mode.st_mode == S_IFDIR)
// 	{
// 		// bash: command: is a directory
// 		exit(126);
// 	}
// 	if (my_search(command, '/') != -1 && open_file(command, command) == 1)
// 		return (command);
// 	return (NULL);
// }

// char	*check_in_env(char **env_paths, char *command)
// {
// 	char	*path;
	
// 	while (env_paths && *env_paths)
// 	{
// 		if (**env_paths)
// 			path = ft_strjoin(*env_paths, command);
// 		else
// 			path = ft_strjoin(".", command);
// 		if (open_file(path, *command) == 1)	
// 		{
// 			free_arr(env_paths);	
// 			return (path);
// 		}
// 		free (path);
// 	}
// 	return (NULL);
// }

// char	*get_path(char *command)
// {
// 	char		*path;
// 	char		**env_paths;

// 	path = first_check(command);
// 	if (path)
// 		return (path);
// 	if (my_search(command, '/') == -1 && *command)
// 	{
// 		command = ft_strjoin("/", command);
// 		path = my_getenv(command);
// 		env_paths = my_split(path, ':', 1);
// 		free(path);
// 		if (!env_paths && open_file(command, command) == 1)
// 			return (command);
// 		path = check_in_env(env_paths, command);
// 		if (path)
// 			return (path);
// 		free_arr(env_paths);	
// 	}
// 	// bash: command: No such file or directory
// 	exit (127);
// }

// void	not_builtin(t_data *data, char **arg)
// {
// 	char	*path;

// 	if (arg && *arg)
// 	{
// 		path = get_path(*arg);
// 		update_envp(data);
// 		execve(path, arg, data->envp);
// 		perror(*arg);
// 	}
// }