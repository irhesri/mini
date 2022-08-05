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
void    my_echo(char  **towrite);
int		my_pwd(void);
int		my_cd(char  **path);
int		my_exit(char    **status);

char    *ft_strjoin(char *str1, char *str2);
char    *vr_expand(char *str, int *size);
short   is_special_red(char c);
void    var_exist(char *str, int *pos);
char    *is_quoted(char *str, int *len, char c);
char *is_double_quoted(char *str, int *size);

#endif
