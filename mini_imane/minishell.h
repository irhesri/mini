#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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

typedef struct s_redirection
{
	int		fd;
	int		pipe_id;
	char	*name;
	short	type;
}	t_redirection;

typedef struct s_pipe
{
	int		n;
	int		pipe_id;
	char	**arg;
}	t_pipe;

typedef struct s_data
{
	char	**envp;
	t_list	*env;
	t_list	*exp;
	// t_list	*input;
	// t_list	*output;
}	t_data;

//	PARSE
char	*var_expand(t_list *env, char *str, int *len);
char	*my_getenv(t_list *env, char *str);
char	**expand(t_list *env, char *str, int *len, short b);

//	LIST_FUNCTIONS
void	add_node(t_list *lst, t_node *pos, void *content);

//	FUNCTIONS
int		ft_strncmp(char *str1, char *str2, size_t n);
int		my_search(char *str, char c);					//returns c position or -1 if it didn't exist
char	*my_strdup(char *str, char c);
char	*ft_strjoin(char *str1, char *str2);
size_t	my_size(char **arr, char *str);
char	*free_join(char *str1, char *str2, short b);
char	**array_realloc(char **arr, char *str, short b);


//	BUILTINS
void	env(t_list *env);
void	export(t_data *data, char **arg);
void	unset(t_data *data, char **arg);

//	ENV_FUNCTIONS
void	init_env(t_data *data, char **envp);			//call it at the begining of the program
void	update_envp(t_data *data);
t_node	*getenv_node(t_node *head, char *str);
t_node	*get_position(t_node *head, char *str);
// int		env_regex(char *str, short b);
short	env_regex(char *str, short b);

char	**my_split(char *str, char c, short b);


// MAKE IT READABLE
short	is_digit(char c);
short	is_alphabet(char c);

#endif