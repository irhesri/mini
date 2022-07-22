# include "minishell.h"

static void	add_front(t_list *lst, t_node *new)
{
	if (!lst->head)
	{
		lst->head = new;
		lst->last = new;
		return;
	}
	new->next = lst->head;
	lst->head = new;
}

void	add_node(t_list *lst, t_node *pos, char *str)
{
	t_node *new;

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

void	delete_node(t_list *lst, t_node *to_delete)
{
	t_node	*tmp;
	t_node	*head;

	if (!lst->head || !to_delete)
		return ;
	lst->size--;
	if (lst->head == to_delete)
	{
		tmp = lst->head;
		lst->head = lst->head->next;
		if (!lst->head)
			lst->last = NULL;
	}
	head = lst->head;
	while (head->next != to_delete)
		head = head->next;
	tmp = head->next;
	head->next = tmp->next;
	if (!tmp->next)
		lst->last = head;
	free (tmp->str);
	free (tmp);
}

