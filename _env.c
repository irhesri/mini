#include "minishell.h"

static void	add_front(t_list *lst, t_node *new)
{
	if (!lst->head)
	{
		lst->head = new;
		lst->last = new;
		return ;
	}
	new->next = lst->head;
	lst->head = new;
}

void	add_node(t_list *lst, t_node *pos, char *str)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->str = str;
	new->next = NULL;
	lst->size++;
	if (!lst->head || !pos)
	{
		add_front(lst, new);
		return ;
	}
	new->next = pos->next;
	pos->next = new;
	if (!new->next)
		lst->last = new;
}

void	init_env(t_data *data, char **envp)
{
	char	*str;
	t_list	*exp;
	t_list	*env;

	env = malloc(sizeof(t_list));
	exp = malloc(sizeof(t_list));
	env->head = NULL;
	env->last = NULL;
	exp->head = NULL;
	env->size = 0;
	exp->size = 0;
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
	data->envp = NULL;
	update_envp(data);
}

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
		data->envp[++i] = head->str;
		head = head->next;
	}
}

void	env(t_list *env)
{
	t_node	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}
