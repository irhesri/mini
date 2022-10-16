/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:48:49 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/16 13:08:48 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	modif_env(t_data *data, char *oldpwd)
{	
	char	*update[4];
	int		i;

	i = 0;
	if (getenv_node(get_exp(NULL)->head, "OLDPWD"))
		update[i++] = ft_strjoin("OLDPWD=", oldpwd);
	if (getenv_node(get_exp(NULL)->head, "PWD"))
	{
		update[i] = malloc(sizeof(char) * MAXPATHLEN);
		if (!update[i])
			exit (write(STDOUT_FILENO, "allocation error\n", 17));
		getcwd(update[i], MAXPATHLEN);
		update[i] = free_join("PWD=", update[i], 2);
		i++;
	}
	update[i] = NULL;
	update[++i] = my_strdup(get_last(NULL, 0), '\0');
	if (update[0])
		export(data, update);
	get_last(update[i], 1);
	i = 0;
	while (update[i])
		free (update[i++]);
}

void	error_case(char *temp)
{
	char	*tmp[2];

	tmp[0] = ft_strjoin("cd: ", temp);
	tmp[1] = ft_strjoin(": ", strerror(errno));
	print_error(tmp[0], tmp[1]);
	free (tmp[0]);
	free (tmp[1]);
	write(1, "\n", 1);
}

void	cd(t_data *data, char **path)
{
	char	*oldpwd;
	char	*temp;

	get_errno(0);
	temp = (*path);
	if (!temp)
	{
		temp = my_getenv("HOME");
		if ((!temp || !(*temp)))
		{
			(!temp) && print_error("cd: HOME not set\n", NULL) && get_errno(1);
			free (temp);
			return ;
		}
	}
	oldpwd = my_getenv("PWD");
	if (chdir(temp) < 0 && get_errno(1))
		error_case(temp);
	else
		modif_env(data, oldpwd);
	if (!(*path))
		free (temp);
	free (oldpwd);
}
