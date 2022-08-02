#include "minishell.h"

short	is_special(char *c)
{
	if ()
	return (0);
}

void	parse_time(char *str)
{
	int		i;
	int		id;
	int		tmp;
	t_pipe	*pipe;
	t_list	*line;

	id = 0;
	i = -1;
	line = malloc(sizeof(t_list));
	line->head = NULL;
	line->last = NULL;
	pipe = malloc(sizeof(t_pipe));
	pipe->pipe_id = id;
	while (str[++i])
	{
		while (str[i] == ' ')
			str[i++] = '\0';
		tmp = is_special(str[i]);
		if (!tmp)
		{
		
		}
		if (tmp && tmp < 5)
			is_redirection()
	}
	
}