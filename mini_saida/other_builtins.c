/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:40:46 by sben-chi          #+#    #+#             */
/*   Updated: 2022/08/11 15:02:36 by sben-chi         ###   ########.fr       */
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
	int	j;
	int	option;

	option = 0;
	i = check_option(towrite, &option);
	while (towrite[i])
	{
		j = -1;
		while (towrite[i][++j])
			write(1, &towrite[i][j], 1);
		i++;
		towrite[i] && write(1, " ", 1);
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
}

/*-----------------END_PWD-----------------*/

/*-------------------CD-------------------*/

void	cd(char	**path)
{
	char	pwd_update[2];
	
	pwd_update[0] = my_getenv("");
	pwd_update[1] = my_getenv();
	if (!(*path))
	{
		*path = my_getenv("HOME");// env vr-modifi
		if (!path)
			printf("$: cd: HOME not set");
		return ;// new_line
	}
	if (chdir(*path) < 0)
		perror("");
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
	printf("here\n");
	printf("exit\n");//test => child process
	exit(nb);
}

/*----------------END_EXIT----------------*/
