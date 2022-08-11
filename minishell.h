/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:38 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/08 12:26:38 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#include <readline/readline.h>
// # include "../mini_saida/h.h"

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
void	init_data(t_data *data);
void	parse_time(t_data *data, char *str);

//	PARSE
char	*var_expand(char *str, int *size);
char	*my_getenv(char *str);
char	**split_expand(char *str, int *len);
char	*is_quoted(char *str, int *len, char c);
char	*new_argument(t_pipe *pipe, char **res2, char *res);
t_pipe	*new_pipe(t_data *data, short b);

//	LIST_FUNCTIONS
void	add_node(t_list *lst, t_node *pos, void *content);
void	delete_node(t_list *lst, t_node *to_delete);

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
// char	**multichar_split(char *str, char *splitters);

// MAKE IT READABLE
short	is_digit(char c);
short	is_alphabet(char c);

// TRASH CAN
void	empty_pipes(t_list *pipes_lst);
void	free_all(t_data *data);
void	my_free(void **content);
void	free_list(t_list *lst, short b);

// GLOBALS
char	*get_last(char *last, int b);
t_list	*get_env(t_list *env);
t_list	*get_exp(t_list *exp);

// DEBUGGING
void	print_2D(char **arr);
void	print_pipes(t_data *data, t_list *pipes);
void	print_list(t_list *lst);


#endif