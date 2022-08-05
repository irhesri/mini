#ifndef H_H
#define H_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include <string.h>
#include <sys/errno.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include "../mini_imane/minishell.h"

//int		code_err = 0;
//const char	*s = "?";

// char    **ft_split(char const *s, char c);	// new_split b = 0
// size_t  ft_strlen(const char *s);	// my_size
// char	*ft_strjoin(const char *s1, const char *s2);
int		ft_atoi(char *str);
char    **arr_join(char **arr1, char **arr2);
void	my_echo(t_pipe *towrite);
void	my_echo(char **arg);
char	*my_pwd(void);
int		my_cd(t_pipe *path, t_data *data);
int		my_exit(t_pipe *status);

#endif
