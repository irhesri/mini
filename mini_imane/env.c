#include "minishell.h"
// initialise enviroment and export list
void	init_env(t_data *data, char **envp)
{
	char	*str;

	while (envp && *envp)
	{
		str = my_strdup(*envp, '\0');
		if (**envp != '_' || (**envp && (*envp)[1] != '='))
		{
			add_node(data->env, data->env->last, str);
			add_node(data->exp, get_position(data->exp->head, *envp), str);
		}
		envp++;
	}
	str = my_strdup("OLDPWD", '\0');
	add_node(data->exp, get_position(data->exp->head, str), str);
	str = my_strdup("_=/usr/bin/env", '\0');
	add_node(data->env, data->env->last, str);
	data->envp = NULL;
	update_envp(data);
}

// update **envp for excve if envp is null
void	update_envp(t_data *data)
{
	int		i;
	t_node	*head;

	if (data->envp)
		return ;
	data->envp = malloc(sizeof(char **) * data->env->size);
	head = data->env->head;
	i = -1;
	while (head)
	{
		data->envp[++i] = head->content;
		head = head->next;
	}
}

// get enviroment variable data
char	*my_getenv(char *str)
{
	int		i;
	t_list	*env;
	t_node	*node;

	env = get_env(NULL);
	node = getenv_node(env->head, str);
	if (!node)
		return (NULL);
	str = (char *)node->content;
	i = my_search(str, '=');
	str = my_strdup(str + i + 1, '\0');
	return (str);
}

// print enviroment variables (env)
void	env(void)
{
	t_node	*tmp;
	t_list	*env;

	env = get_env(NULL);
	tmp = env->head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
