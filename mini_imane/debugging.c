#include "minishell.h"

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
		printf("--------->last argument :\n%s\n", get_last(NULL, 0));
		printf("****************************\n");
		tmp=tmp->next;
	}
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