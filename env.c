#include "minishell.h"

// int	my_getenv(char **env, char *var)
// {
// 	int		i;
// 	size_t	len;

// 	i = -1;
// 	len = my_strlen(var);
// 	while (env[++i])
// 	{
// 		if (!strncmp(env[i], *var))
// 			return (i);
// 	}
// 	return (-1);
// }

void	env(t_data *data, char **arg/*only ones with =*/, short b)
{
	int		i;
	char	**env;
	size_t	size;

	if (b)
	{
		data->env_size += my_size(arg, NULL, 2);
		env = malloc(data->env_size + 1);
		i = 0;
		while (*(data->env + i))
			env[i++] = *data->env;
		while (*arg)
			env[i++] = *arg++;
		env[i] = NULL;
		if (b == 2)
			free (data->env);
		data->env = env;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	**arr;
	int		i, j;

	data = malloc(sizeof(t_data));
	data->env = envp;
	data->b = 1;
	data->env_size = my_size(envp, NULL, 2);


	i = 0;
	while (i < 3)
	{
		while (j < 5)
		{
			arr[i][j] = 'a';
			j++;
		}
		i++;
	}
	env(data, arr, 1);
	
	i = 0;
	while (*(data->env + i))
		printf("%s\n", *(data->env + i++));

	// printf("%s\n", getenv("Z"));
}