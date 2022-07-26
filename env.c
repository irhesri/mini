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

void	add_node(t_list *lst, t_node *pos, void *content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->content = content;
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

	data->env = malloc(sizeof(t_list));
	data->exp = malloc(sizeof(t_list));
	data->env->head = NULL;
	data->env->last = NULL;
	data->exp->head = NULL;
	data->env->size = 0;
	data->exp->size = 0;
	while (envp && *(envp + 1))
	{
		str = my_strdup(*envp, '\0');
		add_node(data->env, data->env->last, str);
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
