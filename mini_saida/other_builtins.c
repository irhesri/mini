#include "h.h" 



/*-------------------ECHO-------------------*/

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

void	my_pwd(void)
{
	char *path;

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

//reimplement

void	my_cd(char	**path)
{
	//test if old pwd will change it in envp
	//test if home unset $pwd & $oldpwd will work normally 
//	char	**up_pwd;
	char	*var;

//	var = my_getenv(data->env, "PWD");

	if (!path[1])
		path[1] = getenv("HOME");// env vr-modif
	if (chdir(path[1]) < 0)
		perror("");
//	up_pwd[1] = free_join(my_strdup("PWD=", '\0'), my_pwd(), 0);
//	up_pwd[2] = NULL;
}

/*------------------END_CD------------------*/

/*------------------EXIT------------------*/

void	my_exit(char	**status)
{
	long long nb;

	if (!status[1])
		exit(0);
	nb = ft_atoi(status[1]);
	if (status[2])
	{
		//retest this case : exit param1 param2 ..
		printf("sben-chi: exit: too many arguments\n");
	//	code_err = 1;
	}
	printf("exit\n");//test => child process
	exit(nb);
}

/*----------------END_EXIT----------------*/
