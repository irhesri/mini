//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:38 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/12 11:46:53 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include <sys/param.h>
# include <string.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

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
    int        n;
    int        fd[2];
    int        pipe_id;
    char    	**arg;
    // short   	 error;
    t_list    *redirections;
}    t_pipe;

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
void	init_files(t_data *data);
short	parse_time(t_data *data, char *str);


//	PARSE
char	*var_expand(char *str, int *size);
char	*my_getenv(char *str);
char	**split_expand(char *str, int *len);
char	*is_quoted(char *str, int *len, char c);
char	*new_argument(t_pipe *pipe, char **res2, char *res);
t_pipe	*new_pipe(t_data *data, short b);

// EXECUTION
void	not_builtin(t_data *data, char **arg);
void	run_commands(t_data *data, t_list *pipes);

//	LIST_FUNCTIONS
void	add_node(t_list *lst, t_node *pos, void *content);
void	delete_node(t_list *lst, t_node *to_delete);

//	LIBFT
int		ft_strncmp(char *str1, char *str2, size_t n);
int		my_search(char *str, char c);					//returns c position or -1 if it didn't exist
char	*ft_strjoin(char *str1, char *str2);
char	*ft_itoa(int n);

// FUNCTIONS

int	my_dup2(int *newfd, int oldfd);
char	**array_realloc(char **arr, char *str, short b);
void	print_error(char *str1, char *str2);
short	ft_putstr(char *str);

//	BUILTINS
void	env(void);
void	export(t_data *data, char **arg);
void	unset(t_data *data, char **arg);
void	commands_call(t_data *data, char **arg);

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
short	is_alphanum(char c);
short	is_builtin(char *arg);
short	is_limiter(char *c);

// TRASH CAN
void	empty_pipes(t_list *pipes_lst);
void	free_all(t_data *data);
void	my_free(void **content);
void	free_list(t_list *lst, short b);
void	free_arr(char **arr);

// GLOBALS
int		get_errno(int n);
char	*get_last(char *last, int b);
char	*get_bash_name(char *str);
t_list	*get_env(t_list *env);
t_list	*get_exp(t_list *exp);

// DEBUGGING
void	print_2D(char **arr);
void	print_pipes(t_data *data, t_list *pipes);
void	print_list(t_list *lst);
void	print_arg(t_data *data, char **arg);

// MINI_SAIDA
void    echo(char **towrite);
void    pwd(void);
void	cd(t_data *data, char **path);
void    my_exit(t_data *data, char **status);
int        ft_atoi(char *str);
char    **arr_join(char **arr1, char **arr2);
char    *is_double_quoted(char *str, int *pos);
void    is_redirection(t_pipe *pipe, char *str, int *i, short type);

#endif