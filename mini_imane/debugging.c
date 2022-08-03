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

void	print_pipes(t_list *pipes)
{
	t_node	*tmp;
	
	tmp = pipes->head;
	while (tmp)
	{
		printf("--------->pipe id :\n%d\n", ((t_pipe *)(tmp->content))->pipe_id);
		printf("--------->arguments [%d]:\n", ((t_pipe *)(tmp->content))->n);
		print_2D(((t_pipe *)(tmp->content))->arg);
		printf("--------->last argument :\n%s\n", ((t_pipe *)(tmp->content))->last_arg);
		printf("****************************\n");
		tmp=tmp->next;
	}
	
}