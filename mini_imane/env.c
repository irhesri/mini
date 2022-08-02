#include "minishell.h"
// initialise enviroment and export list
void	init_env(t_data *data, char **envp)
{
	char	*str;

	data->env = malloc(sizeof(t_list));
	data->exp = malloc(sizeof(t_list));
	(data->env)->head = NULL;
	(data->env)->last = NULL;
	(data->exp)->head = NULL;
	(data->exp)->last = NULL;
	data->env->size = 0;
	data->exp->size = 0;
	while (envp && *envp)
	{
		str = my_strdup(*envp, '\0');
		add_node(data->env, data->env->last, str);
		// if (**envp != '_' || (**envp && *envp[1] != '='))
			add_node(data->exp, get_position(data->exp->head, *envp), str);
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
char	*my_getenv(t_list *env, char *str)
{
	int		i;
	t_node	*node;

	node = getenv_node(env->head, str);
	if (!node)
		return (NULL);
	str = (char *)node->content;
	i = my_search(str, '=');
	str = my_strdup(str + i + 1, '\0');
	return (str);
}

// print enviroment variables (env)
void	env(t_list *env)
{
	t_node	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
