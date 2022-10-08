/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:40:46 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/08 12:59:12 by sben-chi         ###   ########.fr       */
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
	if (!getcwd(path, MAXPATHLEN))
	{
		perror("");
		exit(0);
	}
	printf("%s\n", path);
	free(path);
}

char	*my_pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * MAXPATHLEN);
	if (!path)
		return (NULL);
	if (!getcwd(path, MAXPATHLEN))
	{
		perror("");
		exit(0);
	}
	return (path);
}

/*-----------------END_PWD-----------------*/

/*-------------------CD-------------------*/

void    cd(t_data *data, char **path)
{
	char	*pwd_update[3];
	char	*temp;
   
	temp = NULL;
	pwd_update[0] = my_getenv("PWD");
	pwd_update[1] = my_getenv("OLDPWD");
	pwd_update[2] = NULL;
	if (!pwd_update[0] && pwd_update[1])
		pwd_update[1] = my_pwd();
	temp = (*path);
	if (!temp)
	{
		temp = my_getenv("HOME");// env vr-modifi
	//	printf("%s\n", temp);
		if (!temp || !(*temp))
		{
			!temp && printf("$: cd: HOME not set\n");
			return ;// new_line
		}
	}
	if (chdir(temp) < 0)
		perror(">>>");
	if (pwd_update[0] && !pwd_update[1])
		pwd_update[0] = my_pwd();
	else if (pwd_update[0] && pwd_update[1])
	{
		pwd_update[1] = pwd_update[0];
		pwd_update[0] = my_pwd();
	}
	//join name= + value;
	//export(data, pwd_update);
}

/*------------------END_CD------------------*/

/*------------------EXIT------------------*/

void	my_exit(t_data *data, char **status)
{
	long long	nb;

	if (!status[0])
		exit(0);
	nb = ft_atoi(status[0]);
	if (status[1])
	{
		//retest this case : exit param1 param2 ..
		printf("sben-chi: exit: too many arguments\n");
		return ;
		//	code_err = 1;
	}
	printf("exit\n");//test => child process
	free_exit(data, nb);
}

/*----------------END_EXIT----------------*/
