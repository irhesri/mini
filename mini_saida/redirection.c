#include "h.h"

char	*normal_chars(char *str, int *i, short b)
{
	int	j;

	j = *i;
	while (str[*i] && !is_special_red(str[*i]) && str[*i] != 39 && str[*i] != 34)
	{
		if (!b && str[*i] == '$') 
			break ;
		(*i)++;	
	}
	return (my_strdup(&str[j], str[(*i)]));
}

void	ft_error(char *str, char **name, int *i)
{
	*name = free_join(*name, normal_chars(str, i, 1), 0);
	printf ("$: %s: ambiguous redirect\n", *name);
	free(*name);
	*name = NULL;

}

int	here_doc_case(char *str, t_redirection *red, int *i)
{
	while (str[*i] && !is_special_red(str[*i]))
	{
		if (str[*i] && (str[*i] == 34 || str[*i] == 39) && (*i)++)
		{
		    red->fd = -2;
			red->name = free_join(red->name, is_quoted(str, i, str[*i - 1]), 0);
		}
		else
			red->name = free_join(red->name, normal_chars(str, i, 1), 0);
	}
	return (1);
}

int	valide_name(char **name, char *str, int *i)
{
    char    **var;
    int     len;

    var = NULL;
	len = 0;
    while (str[*i] && !is_special_red(str[*i]))
    {
        if (str[*i] == 39 && ++(*i))
            *name = free_join(*name, is_quoted(str, i, str[*i - 1]), 0);
		else if (str[*i] == 34 && ++(*i))
            *name = free_join(*name, is_double_quoted(str, i), 0);
        else if (str[*i] == '$' && ++(*i))
        {
            var = split_expand(str, i);
            if (*(var + 1))
            {
				ft_error(str, name, i);
				return 0;
            }
            *name = free_join(*name, *var, 1);
        }
		else
			*name = free_join(*name, normal_chars(str, i, 0), 0);
		*i += len;
	}
	return (1);
}

void	get_name(t_redirection *red, char *str, int *i, short type)
{
	int	k;

	k = *i + 1;
	if (str[*i] && (is_special_red(str[*i]) || str[*i] == '#'))
    {
    	printf("$: syntax error near unexpected token `%c'\n", str[*i]);
		red->name = NULL;
		return ;//exit
    }
	(type == 7) && here_doc_case(str, red, i);
	if (str[*i] == '$' && !var_expand(str, &k))
	{
		ft_error(str, &red->name, i);
		return ;
	}
	(type != 7) && valide_name(&(red->name), str, i);
}

int mode(short type)
{
	if (type == 6)
		return (O_RDONLY);
	if (type == 7)
		return (0);
	if (type == 8)
		return (O_TRUNC);
	if (type == 9)
		return (O_APPEND);
	return (-1);
}

void	is_redirection(t_pipe *pipe, char *str, int *i, short type)
{
	t_redirection   *red;

	red = malloc(sizeof(t_redirection));
	if (!red)
		return ;
	red->fd = 0;
	red->mode = mode(type);
	red->name = NULL;
//	printf("%s\n", str);
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	get_name(red, str, i, type);
	printf("%s $%d\n", red->name, red->fd);
	if (type == 6 || type == 7)
		add_node(pipe->input, pipe->input->last, red);
	else
		add_node(pipe->output, pipe->output->last, red);
//	t_redirection *t = pipe->input->last->content;
//	printf("> %s\n", t->name);
}

// int main()
// {
// 	char	*l;
// 	while (1)
// 	{
// 		l = readline("> ");
// 		add_history(l);
// 		is_redirection(l, 6);
// 	}
// }
