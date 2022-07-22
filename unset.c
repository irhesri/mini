# include "minishell.h"

void	unset(t_list *lst, char *str)
{
	t_node	*node;

	node = my_getenv(lst->head, str);
	delete_node(lst, node);
}