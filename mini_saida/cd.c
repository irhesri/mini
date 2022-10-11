/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:48:49 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 15:22:10 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	modif_env(t_data *data, char *oldpwd)
{	
	char	*update[3];
	int		i;

	i = 0;
	if (getenv_node(get_exp(NULL)->head, "OLDPWD"))
		update[i++] = ft_strjoin("OLDPWD=", oldpwd);
	if (getenv_node(get_exp(NULL)->head, "PWD"))
	{
		update[i] = malloc(sizeof(char) * MAXPATHLEN);
		getcwd(update[i], MAXPATHLEN);
		update[i] = ft_strjoin("PWD=", update[i]);
		i++;
	}
	update[i] = NULL;
	if (update[0])
		export(data, update);
}

void	cd(t_data *data, char **path)
{
	char	*oldpwd;
	char	*temp;

	temp = NULL;
	get_errno(0);
	oldpwd = my_getenv("PWD");
	temp = (*path);
	if (!temp)
	{
		temp = my_getenv("HOME");
		if ((!temp || !(*temp)) && get_errno(1))
		{
			write(2, "$: cd: HOME not set\n", 20);
			return ;
		}
	}
	if (chdir(temp) < 0 && get_errno(1))
	{
		print_error("cd: ", temp);
		write(1, ": ", 2);
		perror("");
	}
	modif_env(data, oldpwd);
}
