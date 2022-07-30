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

// add node to lst after pos
// pos == NULL to add in the front
// pos == lst->last to add in the back
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
