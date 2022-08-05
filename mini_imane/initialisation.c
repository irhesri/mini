#include "minishell.h"


void	init_data(t_data *data, char *str)
{
	t_list	*lst;

	data->pipes = malloc(sizeof(t_list));
	(data->pipes)->head = NULL;
	(data->pipes)->last = NULL;
	lst = malloc(sizeof(t_list));
	lst->head = NULL;
	lst->last = NULL;
	lst->size = 0;
	get_env(lst);
	lst = malloc(sizeof(t_list));
	lst->head = NULL;
	lst->last = NULL;
	lst->size = 0;
	get_exp(lst);
}

// initialise enviroment and export list
void	init_env(t_data *data, char **envp)
{
	char	*str;

	while (envp && *envp)
	{
		if (**envp != '_' || (**envp && (*envp)[1] != '='))
		{
			str = my_strdup(*envp, '\0');
			add_node(get_env(NULL), (get_env(NULL))->last, str);
			add_node(get_exp(NULL), get_position((get_exp(NULL))->head, *envp), str);
		}
		envp++;
	}
	str = my_strdup("OLDPWD", '\0');
	add_node(get_exp(NULL), get_position((get_exp(NULL))->head, str), str);
	str = my_strdup("_=/usr/bin/env", '\0');
	add_node(get_env(NULL), (get_env(NULL))->last, str);
	data->envp = NULL;
	update_envp(data);
}
