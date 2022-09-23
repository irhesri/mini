/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:00 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/23 18:38:31 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_2D(char **arr)
{
	while (arr && *arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
	printf("\n");
}

void	print_pipes(t_data *data, t_list *pipes)
{
	t_node	*tmp;
	
	tmp = pipes->head;
	printf("NUMBER OF PIPES : %d\n", data->nbr_pipes);
	while (tmp)
	{
		printf("--------->pipe id :\n%d\n", ((t_pipe *)(tmp->content))->pipe_id);
		printf("--------->arguments [%d]:\n", ((t_pipe *)(tmp->content))->n);
		print_2D(((t_pipe *)(tmp->content))->arg);
		printf("****************************\n");
		tmp=tmp->next;
	}
	printf("--------->last argument :\n%s\n", get_last(NULL, 0));
}

void	print_list(t_list *lst)
{
	t_node	*node;

	node = lst->head;
	while (node)
	{
		printf("%s\n", (char *)(node->content));
		node = node->next;
	}
	
}

void	print_arg(t_data *data, char **arg)
{
	while (arg && *arg)
	{
		printf("%s\n", *arg);
		arg++;
	}
}