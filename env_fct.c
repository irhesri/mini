#include "minishell.h"

void	init_env(t_data *data, char **envp)
{
	t_list	*exp;
	t_list	*env;
	char	*str;

	env = malloc(sizeof(t_list));
	exp = malloc(sizeof(t_list));
	env->head = NULL;
	exp->head = NULL;
	env->last = NULL;
	exp->last = NULL;
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

t_node *node;
char	*str;

node = my_getenv(DATA->ENV->HEAD, "LANG");
str = node->str + my_search(node->str, '=') + 1;