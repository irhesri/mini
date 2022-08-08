#include "../mini_imane/minishell.h"
void	print_arg(char **arg)
{
	while (arg && *arg)
	{
		printf("%s\n", *arg);
		arg++;
	}
	
}
void	builtins_call(t_data *data, char **arg)
{
	int			i;
	short		b;
	static void	(*ptr[8])();
	static char	*call[10] = {"echo", "pwd", "cd", "exit", "env", "export", "unset"};

	if (!ptr[0])
	{
		ptr[0] = print_arg;
		ptr[1] = my_echo;
		ptr[2] = my_pwd;
		ptr[3] = my_cd;
		ptr[4] = my_exit;
		ptr[5] = env;
		ptr[6] = export;
		ptr[7] = unset;
	}
	b = 0;
	i = -1;
	while (!b && arg && ++i < 8)
		b = !ft_strncmp(call[i], *arg, 10) * (i + 1);
	if (b > 5 && arg)
		ptr[b](data, arg + 1);
	else
		ptr[b](arg + (b != 0));
}
