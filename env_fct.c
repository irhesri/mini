#include "minishell.h"

void	init_env(t_data *data, char **envp)
{
	char	*str;
	t_list	*exp;
	t_list	*env;

	env = malloc(sizeof(t_list));
	exp = malloc(sizeof(t_list));
	env->head = NULL;
	exp->head = NULL;
	data->env->size = 0;
	data->exp->size = 0;
	while (envp && *envp)
	{
		str = my_strdup(*envp, '\0');
		add_node(env, env->last, str);
		add_node(exp, get_position(exp->head, *envp), str);
		envp++;
	}
	str = my_strdup("OLDPWD", '\0');
	add_node(exp, get_position(exp->head, str), str);
	data->env = env;
	data->exp = exp;
	data->b = 0;
}

void	init_envp(t_data *data)
{
	int		i;
	t_node	*head;

	if (data->b == 2)
		return ;
	if (data->b == 1)
		free(data->envp);
	data->envp = malloc(sizeof(char **) * data->env->size);
	head = data->env->head;
	i = -1;
	while (head)
	{
		data->envp[++i] = head->str;
		head = head->next;
	}
	data->b = 2;	
}

t_node	*my_getenv(t_node *head, char *str)
{
	size_t	size;

	size = my_size(NULL, str);
	while (head)
	{
		if (!my_strncmp(head->str, str, size))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_node	*get_position(t_node *head, char *str)
{
	size_t	size;
	t_node	*pos;

	size = my_size(NULL, str) + 1;
	if (!head || my_strncmp(head->str, str, size) > 0)
		return (NULL);
	pos = head;
	head = head->next;
	while (head && (my_strncmp(head->str, str, size) < 0))
	{
		pos = head;
		head = head->next;
	}
	return (pos);
}

// t_node *node;
// char	*str;

// node = my_getenv(DATA->ENV->HEAD, "LANG");
// str = node->str + my_search(node->str, '=') + 1;