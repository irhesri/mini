#include "minishell.h"

t_list	*get_env(t_list *env)
{
	static t_list *g_env;

	if (!g_env)
		g_env = env;
	return (g_env);
}

char	*get_last(char *last, int b)
{
	static char *g_last;

	if (b)
	{
		free (g_last);
		g_last = last;
	}
	return (g_last);
}