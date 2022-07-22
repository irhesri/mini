#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*last;
	size_t	size;
}	t_list;

typedef struct s_data
{
	t_list	*env;
	t_list	*exp;
}	t_data;


//	LIST_FUNCTIONS
void	add_node(t_list *lst, t_node *pos, char *str);
void	delete_node(t_list *lst, t_node *to_delete);


//	FUNCTIONS
size_t	my_size(char **arr, char *str);
short	my_strncmp(char *str1, char *str2, size_t n);
char	*my_strdup(char *str, char c);
int	my_search(char *str, char c);


//	BUILTINS
void	unset(t_list *lst, char *str);

//	ENV_FUNCTIONS
void	init_env(t_data *data, char **envp);
t_node	*my_getenv(t_node *head, char *str);
t_node	*get_position(t_node *head, char *str);

#endif