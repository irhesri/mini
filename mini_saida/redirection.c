#include "h.h"

char	*normal_chars(char *str, int *i, short b)
{
	int	j;

	j = *i;
	while (str[*i] && str[*i] != ' ' && !is_special_red(str[*i]))
	{
		if (!b && str[*i] == '$') 
			break ;
		(*i)++;	
	}
	return (my_strdup(&str[j], str[(*i)]));
}

int	here_doc_case(char *str, t_redirection *red, int *i)
{
	int	len;

	len = 0;
	while (str[*i] && str[*i] != ' ' && !is_special_red(str[*i]))
	{
		if (str[*i] && (str[*i] == 34 || str[*i] == 39))
		{
		    red->fd = -2;
			red->name = free_join(red->name, is_quoted(str + *i + 1, &len, str[*i]), 0);
		}
		else
			red->name = free_join(red->name, normal_chars(str, i, 1), 0);
		*i += len + 1;
	}
	return (1);
}

int	valide_name(char **name, char *str, int *i)
{
    char    **var;
    int     len;

    var = NULL;
	len = 0;
	printf("here\n");
    while (str[*i] && !is_special_red(str[*i]))
    {
        if (str[*i] == 39)
            *name = free_join(*name, is_quoted(str + *i + 1, i, str[*i]), 0);
        else if (str[*i] == 34)
            *name = free_join(*name, is_double_quoted(str + *i + 1, &len), 0);
        else if (str[*i] == '$')
        {
            var = split_expand(str + *i, &len);
            if (*(var + 1))
            {
				*name = free_join(*name, normal_chars(str, i, 1), 0);
                printf ("$: %s: ambiguous redirect\n", *name);
				free(*name);
				*name = NULL;
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
	if (str[*i] && (is_special_red(str[*i]) || str[*i] == '#'))
    {
    	printf("$: syntax error near unexpected token `%c'\n", str[*i]);
		red->name = NULL;      
    }
	(type == 7) && here_doc_case(str, red, i);
	(type != 7) && valide_name(&(red->name), str + *i, i);
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

int is_redirection(t_list *input, t_list *output,  char *str, short type)
{
	t_redirection   *red;
	int             i;

	i = 0;
	red = malloc(sizeof(t_redirection));
	if (!red)
		return (0);
	red->fd = 0;
	red->mode = mode(type);
	while (str[i] && str[i] == ' ')
		i++;
	get_name(red, &str[i], &i, type);
	if (type == 6 || type == 7)
		add_node(input, input->last, red);
	else
		add_node(output, output->last, red);
	return (i);
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
