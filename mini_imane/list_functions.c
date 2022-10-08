/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:31 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/23 21:50:24 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_front(t_list *lst, t_node *new)
{
	if (!lst->head)
	{
		lst->head = new;
		lst->last = new;
		lst->size = 1;
		return ;
	}
	lst->size++;
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
	if (!lst->head || !pos)
	{
		add_front(lst, new);
		return ;
	}
	lst->size++;
	new->next = pos->next;
	pos->next = new;
	if (!new->next)
		lst->last = new;
}

// delete node to_delete 
// get to_delete using getenv_node() function
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
		free (tmp);
		return ;
	}
	head = lst->head;
	while (head->next != to_delete)
		head = head->next;
	tmp = head->next;
	head->next = tmp->next;
	if (!tmp->next)
		lst->last = head;
	free (tmp);
}
