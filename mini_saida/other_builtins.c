#include "../minishell.h" 



//----------------echo-------------------//


int	is_redirection(char *str, int b)
{
//space case with or without \"/'
//
}


/*-------------------ECHO-------------------*/


// char *rp_var(char *str, int *j)
// {	
// 	char	*t;
// 	char	*env_vr;
// 	int		len_path;

// 	len_path = my_strlen(&str[(*j) + 1]);
// 	if (!len_path)
// 		return ("$");
// 	t = strndup(&str[(*j) + 1], len_path);
// 	(*j) += len_path;
// 	env_vr = getenv(t);
// 	if (!env_vr)
// 		return (NULL);
// 	free(t);
// 	return env_vr;
// }

int check_option(char *str, int *option)
{
	int	i;

	i = 1;
	while(str[i] && str[i] == 'n')
		i++;
	*option = !str[i];
	return (*option);
}

void	my_echo(t_pipe *towrite)
{
	int 	i;
	int 	j;
	int		option;

	option = 0;
	i = (towrite->arg[0][0] == '-' && check_option(towrite->arg[0], &option));
	while (towrite->arg[i])
	{
		j = -1;
		while (towrite->arg[i][++j])
			write(1, &towrite->arg[i][j], 1);
		i++;
		towrite->arg[i] && write(1, " ", 1);
	}
	!option && write(1, "\n", 1);
}

/*-----------------END_ECHO-----------------*/



/*-------------------PWD-------------------*/

char	*my_pwd(void)
{
	char *path;

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

int	my_cd(t_pipe *path, t_data *data)
{
	//test if old pwd will change it in envp
	//test if home unset $pwd & $oldpwd will work normally 
	char	**up_pwd;

	up_pwd = malloc(sizeof(char *) * 3);
	up_pwd[0] = free_join("OLDPWD=", my_pwd(), 0);
	if (!path->arg[1])
		path->arg[1] = my_getenv(get_env(NULL) ,"HOME");// env vr-modif
	if (chdir(path->arg[1]) < 0)
		perror("");
	up_pwd[1] = free_join("PWD=", my_pwd(), 0);
	up_pwd[2] = NULL;
	return 1;
}

/*------------------END_CD------------------*/

/*------------------EXIT------------------*/

int	my_exit(t_pipe *status)
{
	long long nb;

	if (!status->arg[1])
		exit(0);
	nb = ft_atoi(status->arg[1]);
	if (status->arg[2])
	{
		//retest this case : exit param1 param2 ..
		printf("sben-chi: exit: too many arguments\n");
		code_err = 1;
	}
	printf("exit\n");
	exit(nb);
}

/*----------------END_EXIT----------------*/


/*----------------------my main--------------------*/


// int	built(char *line)
// {
// 	char	**t;
// 	int		i;

// 	i = 0;
// 	if (!*line)
// 		return -1;	
// 	t = ft_split(line, ' ');
// 	if (!strcmp(t[0], "exit"))
// 		my_exit(t);
// 	if (!strcmp(t[0], "pwd"))
// 		my_pwd();
// 	else if (!strcmp(t[0], "cd"))
// 		my_cd(t);
// 	else if (!strcmp(t[0], "echo"))
// 		my_echo(t + 1);
// 	return (1);
// }

// int main(int ac, char **av)
// {
// 	char *line;
	
// 	while (1)
// 	{
// 		line = readline("sben-chi$ ");
// 		built(line);
// 	}

// }
