#include "h.h" 



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

int check_option(char **str, int *option)
{
    int j;
    int i;

    i = -1;
    while (str[++i] && str[i][0] == '-')
    {
        j = 1;
        while(str[i][j] && str[i][j] == 'n')
            j++;
    }
    *option = (!str[i - 1][j] && j > 1) || i > 1;
    if (i && (str[i - 1][j] || j == 1))
        i--;
    return (i);
}

void    my_echo(char  **towrite)
{
    int     i;
    int     j;
    int     option;

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

int	my_pwd(void)
{
	char *path;

	path = malloc(sizeof(char) * MAXPATHLEN);
	if (!path)
		return (0);
	if (!getcwd(path, MAXPATHLEN))
	{
		perror("");
		exit(0);
	}
	printf("%s\n", path)
	return (1);
}

/*-----------------END_PWD-----------------*/

/*-------------------CD-------------------*/

//reimplement

int	my_cd(char	**path)
{
	//test if old pwd will change it in envp
	//test if home unset $pwd & $oldpwd will work normally 
//	char	**up_pwd;
	char	*var;

//	var = my_getenv(data->env, "PWD");

	if (!path[1])
		path[1] = my_getenv(data->env ,"HOME");// env vr-modif
	if (chdir(path[1]) < 0)
		perror("");
//	up_pwd[1] = free_join(my_strdup("PWD=", '\0'), my_pwd(), 0);
//	up_pwd[2] = NULL;
	return 1;
}

/*------------------END_CD------------------*/

/*------------------EXIT------------------*/

int	my_exit(char	**status)
{
	long long nb;

	if (!status[1])
		exit(0);
	nb = ft_atoi(status[1]);
	if (status[2])
	{
		//retest this case : exit param1 param2 ..
		printf("sben-chi: exit: too many arguments\n");
		code_err = 1;
	}
	printf("exit\n");//in child process
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
/*
int main(int ac, char **av)
{
	char *line;
	
	char *path;

	path = malloc(sizeof(char) * MAXPATHLEN);
	if (!path)
		return (NULL);
	if (!getcwd(path, MAXPATHLEN))
	{
		perror("error:");
		exit(0);
	}
	printf("%s\n", path);

}*/
