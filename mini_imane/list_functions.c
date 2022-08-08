/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:31 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/08 13:02:44 by irhesri          ###   ########.fr       */
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
