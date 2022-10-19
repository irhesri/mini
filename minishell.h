/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:10:38 by irhesri           #+#    #+#             */
/*   Updated: 2022/10/19 21:59:48 by imane            ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

//	list of nodes	//
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
	int		fd[2];
	int		pipe_id;
	char	**arg;
	t_list	*redirections;
}	t_pipe;

// ******************** //
typedef struct s_data
{
	int		nbr_pipes;
	char	**paths;
	char	**envp;
	char	**history;
	short	here_doc_nbr;
	size_t	history_size;
	size_t	history_lines;
	t_list	*pipes;
}	t_data;

// INITIALISATION		---->		call it at the begining of the program
void		init_env(t_data *data, char **envp);			
short		init_files(t_data *data);
short		parse_time(t_data *data, char *str, int i);
short		init_here_doc(t_data *data);

//	PARSE
char		*var_expand(char *str, int *size);
char		*my_getenv(char *str);
char		**split_expand(char *str, char *res, int *len);
char		*is_quoted(char *str, int *len, char c);
char		*is_double_quoted(char *str, int *pos);
char		*normal_chars(char *str, int *i, short b);
short		is_special_red(char c);
short		is_redirection(t_pipe *pipe, char *str, int *i, short type);
t_pipe		*new_pipe(t_data *data, short b);

// EXECUTION
void		not_builtin(t_data *data, char **arg);
void		run_commands(t_data *data, t_list *pipes);
void		handle_sigint(int sig);
void		set_termios_echoctl(void);
void		reset_termios_echoctl(void);
short		update_path(t_data *data, char *str);
short		heredoc(int fd, t_redirection *red);

//	LIST_FUNCTIONS
void		add_node(t_list *lst, t_node *pos, void *content);
void		delete_node(t_list *lst, t_node *to_delete);

//	LIBFT
int			ft_strncmp(char *str1, char *str2, size_t n);
int			my_search(char *str, char c);
char		*ft_strjoin(char *str1, char *str2);
char		*ft_itoa(int n);
long long	ft_atoi(char *str);

// FUNCTIONS
int			ft_strtrim(char *str, int i);
int			my_dup2(int *newfd, int oldfd);
char		**array_realloc(char **arr, char *str, short b);
void		reset_exit(int n);
short		print_error(char *str1, char *str2);
short		ft_putstr(char *str, int fd);

//	BUILTINS
void		env(void);
void		export(t_data *data, char **arg);
void		unset(t_data *data, char **arg);
void		echo(char **towrite);
void		pwd(void);
void		cd(t_data *data, char **path);
void		my_exit(t_data *data, char **status);
void		commands_call(t_data *data, char **arg);

// HISTORY
void		history(t_data *data, char **arg);
void		my_add_history(t_data *data, char *str);
short		display_history(t_data *data);

//	ENV_FUNCTIONS
void		update_envp(t_data *data);
short		env_regex(char *str, short b);
t_node		*getenv_node(t_node *head, char *str);
t_node		*get_position(t_node *head, char *str);

// NEW LIBFT
char		**my_split(char *str, char c, short b);
char		*my_strdup(char *str, char c);
char		*free_join(char *str1, char *str2, short b);
size_t		my_size(char **arr, char *str);
long long	my_atoi(char *str);

// MAKE IT READABLE
short		is_digit(char c);
short		is_alphanum(char c);
short		is_builtin(char *arg);
short		is_limiter(char *c);
short		is_directory(char *path);

// TRASH CAN
char		**free_arr(char **arr);
void		empty_pipes(t_list *pipes_lst);

// GLOBALS
int			get_errno(int n);
char		*get_last(char *last, int b);
char		*get_bash_name(char *str);
t_list		*get_env(t_list *env);
t_list		*get_exp(t_list *exp);

#endif
