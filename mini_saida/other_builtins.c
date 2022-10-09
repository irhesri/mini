/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:40:46 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/09 19:39:09 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

/*-------------------ECHO-------------------*/

int	check_option(char **str, int *option)
{
	int	j;
	int	i;

	i = -1;
	while (str[++i] && str[i][0] == '-')
	{
		j = 1;
		while (str[i][j] && str[i][j] == 'n')
			j++;
	}
	*option = ((i > 0 && !str[i - 1][j] && j > 1) || i > 1);
	if (i && (str[i - 1][j] || j == 1))
		i--;
	return (i);
}

void	echo(char **towrite)
{
	int	i;
	int	option;

	option = 0;
	i = check_option(towrite, &option);
	get_errno(0);
	while (towrite[i])
	{
		write(1, towrite[i], my_size(NULL, towrite[i]));
		towrite[++i] && write(1, " ", 1);
	}
	!option && write(1, "\n", 1);
}

/*-----------------END_ECHO-----------------*/

/*-------------------PWD-------------------*/

void	pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * MAXPATHLEN);
	if (!path)
		return ;
	get_errno(0);
	if (!getcwd(path, MAXPATHLEN) && get_errno(1))
	{
		perror("");
		return ;
	}
	printf("%s\n", path);
	free(path);
}

/*-----------------END_PWD-----------------*/

/*-------------------CD-------------------*/

void	modif_env(t_data *data, char *oldpwd)
{	
	char	*update[3];
	int		i;

	i = 0;

	if (getenv_node(get_exp(NULL)->head, "OLDPWD"))
		update[i++] = ft_strjoin("OLDPWD=", oldpwd);
	if(getenv_node(get_exp(NULL)->head, "PWD"))
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

void    cd(t_data *data, char **path)
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
		perror("$: ");
	modif_env(data, oldpwd);
}

/*------------------END_CD------------------*/

/*------------------EXIT------------------*/

void	my_exit(t_data *data, char **status)
{
	long long	nb;

	get_errno(0);
	if (!status[0])
		free_exit(data, 0);
	nb = ft_atoi(status[0]);
	if (status[1] && get_errno(1))
	{
		write(2, "exit\nsben-chi: exit: too many arguments\n", 40);
		return ;
	}
	write(1, "exit\n", 5);
	free_exit(data, nb);
}

/*----------------END_EXIT----------------*/
