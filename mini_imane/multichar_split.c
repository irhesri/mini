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
		splitters++;
	}
	return (0);
}

static void	get_size(t_list *size, char *str, char *splitters)
{
	int		i;
	int		*word_size;

	while (*str)
	{
		i = 0;
		while (*str && is_splitter(splitters, *str))
			str++;
		while (*str && !is_splitter(splitters, *str))
		{
			str++;
			i++;
		}
		if (i)
		{
			word_size = malloc(sizeof(int));
			(*word_size) = i;
			add_node(size, size->last, word_size);
		}
	}
}

static	char	**fill(t_list *size, char *str, char *splitter)
{
	int		i;
	int		j;
	int		len;
	char	**words;
	t_node	*node;

	words = (char **) malloc(sizeof(char *) * (size->size + 1));
	!words && my_error(words, 0);
	i = -1;
	node = size->head;
	while (node)
	{
		len = *((int *)(node->content));
		words[++i] = malloc((len + 1));
		!words[i] && my_error(words, i);
		while (*str && is_splitter(splitter, *str))
			str++;
		j = -1;
		while (++j < len)
			words[i][j] = *str++;
		words[i][j] = '\0';
		node = node->next;
	}
	words[++i] = NULL;
	return (words);
}

char	**multichar_split(char *str, char *splitters)
{
	char	**words;
	t_list	*size;
	t_node	*node;
	t_node	*tmp;

	if (!str || !splitters)
		return (NULL);
	while (*str && is_splitter(splitters, *str))
		str++;
	size = malloc(sizeof(t_list));
	size->head = NULL;
	size->last = NULL;
	get_size(size, str, splitters);
	words = fill(size, str, splitters);
	/*if (len)
		*len = size->data;*/
	free_list(size, 1);
	return (words);
}