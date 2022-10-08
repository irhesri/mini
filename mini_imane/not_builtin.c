/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:48:26 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/13 12:30:49 by sben-chi         ###   ########.fr       */
=======
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:48:26 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/25 15:47:52 by imane            ###   ########.fr       */
>>>>>>> 84cc9a9e63354fb5d1eea62784b965f7a64a8153
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
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
	
<<<<<<< HEAD
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
=======
	while (env_paths && *env_paths)
=======
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
			free_exit (NULL, 126);
		}
		print_error(command, ": Permission denied\n");
		free_exit (NULL, 126);
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
		free_exit (NULL, 126);
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
>>>>>>> 84cc9a9e63354fb5d1eea62784b965f7a64a8153
	{
		if (**paths)
			path = ft_strjoin(*paths, command);
		else
			path = ft_strjoin(".", command);
<<<<<<< HEAD
		if (open_file(path, command) == 1)	
=======
		if (open_file(path, command + 1) == 1)
>>>>>>> 84cc9a9e63354fb5d1eea62784b965f7a64a8153
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
>>>>>>> 885dbf00214b6e49c3cd8c7eff0930fd730c3cfc

// char	*get_path(char *command)
// {
// 	char		*path;
// 	char		**env_paths;

<<<<<<< HEAD
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
=======
	path = first_check(command);
	if (path)
		return (path);
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
	free_exit (NULL, 127);
	return (NULL);
}
>>>>>>> 84cc9a9e63354fb5d1eea62784b965f7a64a8153

// void	not_builtin(t_data *data, char **arg)
// {
// 	char	*path;

<<<<<<< HEAD
// 	if (arg && *arg)
// 	{
// 		path = get_path(*arg);
// 		update_envp(data);
// 		execve(path, arg, data->envp);
// 		perror(*arg);
// 	}
// }
=======
	if (arg && *arg)
	{
		path = get_path(*arg);
		update_envp(data);
		execve(path, arg, data->envp);
		free(path);
		perror(get_bash_name(NULL));
		free_exit (NULL, errno);
	}
}
>>>>>>> 84cc9a9e63354fb5d1eea62784b965f7a64a8153
