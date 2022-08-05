#include "minishell.h"

t_list	*get_env(t_list *env)
{
	static t_list *g_env;

	if (!g_env)
		g_env = env;
	return (g_env);
}

t_list	*get_exp(t_list *exp)
{
	static t_list *g_exp;

	if (!g_exp)
		g_exp = exp;
	return (g_exp);
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