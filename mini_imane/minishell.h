#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#include <readline/readline.h>
# include "../mini_saida/h.h"

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*last;
	size_t	size;
}	t_list;

// stored in t_list content //
typedef struct s_redirection
{
	int		fd;
	int		mode;
	char	*name;
}	t_redirection;

// stored in t_list content //
typedef struct s_pipe
{
	int		n;
	int		pipe_id;
	char	**arg;
	t_list	*input;
	t_list	*output;
}	t_pipe;

// ******************** //
typedef struct s_data
{
	int		nbr_pipes;
	short	here_doc_nbr;
	char	**envp;
	t_list	*pipes;
}	t_data;

// INITIALISATION		---->		call it at the begining of the program
void	init_env(t_data *data, char **envp);			
void	init_data(t_data *data, char *str);
void	parse_time(t_data *data, char *str);

//	PARSE
char	*var_expand(char *str, int *size);
char	*my_getenv(char *str);
char	**split_expand(char *str, int *len);

//	LIST_FUNCTIONS
void	add_node(t_list *lst, t_node *pos, void *content);

//	LIBFT
int		ft_strncmp(char *str1, char *str2, size_t n);
int		my_search(char *str, char c);					//returns c position or -1 if it didn't exist
char	*ft_strjoin(char *str1, char *str2);

// FUNCTIONS
char	**array_realloc(char **arr, char *str, short b);

//	BUILTINS
void	builtins_call(t_data *data, char **arg);
void	env(void);
void	export(t_data *data, char **arg);
void	unset(t_data *data, char **arg);

//	ENV_FUNCTIONS
void	update_envp(t_data *data);
short	env_regex(char *str, short b);
t_node	*getenv_node(t_node *head, char *str);
t_node	*get_position(t_node *head, char *str);

// NEW LIBFT
char	**my_split(char *str, char c, short b/*, int *len*/);
char	*my_strdup(char *str, char c);
char	*free_join(char *str1, char *str2, short b);
size_t	my_size(char **arr, char *str);

// MAKE IT READABLE
short	is_digit(char c);
short	is_alphabet(char c);

// TRASH CAN
void	empty_pipes(t_list *pipes_lst);
void	free_all(t_data *data);
void	my_free(void **content);

// GLOBALS
char	*get_last(char *last, int b);
t_list	*get_env(t_list *env);
t_list	*get_exp(t_list *exp);

// DEBUGGING
void	print_2D(char **arr);
void	print_pipes(t_data *data, t_list *pipes);
void	print_list(t_list *lst);


//mini_saida
void    is_redirection(t_pipe *pipe, char *str, int *i, short type);
void    my_echo(char  **towrite);
void    m_pwd(void);
void    my_cd(char  **path);
void    my_exit(char    **status);

#endif
