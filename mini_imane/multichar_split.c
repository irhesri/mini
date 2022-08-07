#include "minishell.h"

typedef struct s_struct
{
	int				data;
	struct s_struct	*next;
}	t_struct;

static short	my_error(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free (str[i++]);
	free (str);
	write(1, "allocation error\n", 17);
	exit (1);
}

static void	add_back(t_struct **lst, int n)
{
	static t_struct	*last;
	t_struct		*new;

	new = (t_struct *) malloc(sizeof(t_struct));
	new->data = n;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		last = new;
		return ;
	}
	last->next = new;
	last = new;
}

short	is_splitter(char *splitters, char c)
{
	while (*splitters)
	{
		if (c == *splitters)
			return (1);
	
	}
	return (0);
}

static t_struct	*get_size()
{

}

char	**multichar_split(char *str, char *splitters)
{
	t_struct	*size;
	t_struct	*tmp;
	char		**words;

	if (!str || !splitters)
		return (NULL);
	while (*str && is_splitter(splitters, *str))
		str++;
	size = get_size(str, splitters);
}