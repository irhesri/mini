#include "minishell.h"

short	builtins_call(char *str)
{
	static void	(*ptr[4])();
	short		b;
	
	if (!ptr[0])
	{
		ptr[1] = export;
		ptr[2] = unset;
		ptr[3] = env;
		// ptr[3] = print3;
	}
	b = !ft_strncmp(str, "export", 10) + !ft_strncmp(str, "unset", 10) * 2 + !ft_strncmp(str, "env", 10) * 3;
	(ptr[b])();

}