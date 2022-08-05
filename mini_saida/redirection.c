#include "h.h"



char	*getn_name(/*t_redirection *red, */char *str, int *i, short type)
{
    char    *name;

    name = NULL;
    if (str[*i] && (is_special_red(str[*i]) || str[*i] == '#'))
    {
        printf("$: syntax error near unexpected token `%c'\n", str[*i]);
        return (name);
    }
		return (name);
}

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

int	here_doc_case(char *str, char **name, int *i)
{
	while (str[*i] && str[*i] != ' ' && !is_special_red(str[*i]))
	{
		if (str[*i] && (str[*i] == 34 || str[*i] == 39))
		{
//		     red->fd = -2;
			*name = free_join(*name, is_quoted(str + *i + 1, i, str[*i]), 0);
		}
		else
			*name = free_join(*name, normal_chars(str, i, 1), 0);
	}
	return (1);
}

int	valide_name(char **name, char *str, int *i)
{
    char    **var;
    int     len;

    var = NULL;
    while (str[*i] && !is_special_red(str[*i]))
    {
        if (str[*i] == 39)
            *name = free_join(*name, is_quoted(str + *i + 1, i, str[*i]), 0);
        else if (str[*i] == 34)
            *name = free_join(*name, is_double_quoted(str + *i + 1, i), 0);
        else if (str[*i] == '$')
        {
			printf("here\n");
			printf("%s\n", str + *i + 1);
            var = split_expand(str + *i + 1, &len);
			printf("%s\n", *var);
			return 0;
			/*
			*i += len;
            if (var + 1)
            {
                printf ("$: <file_name>: ambiguous redirect\n");
                *name = NULL;
                return 0;
            }
            *name = free_join(*name, *var, 1);
        }*/}
		else
			*name = free_join(*name, normal_chars(str, i, 0), 0);
	}
	return (1);
}


char	*get_name(char *str, int *i, short type)
{
	char 	*name;

	name = NULL;
	(type == 7) && here_doc_case(str, &name, i);
	(type != 7) && valide_name(&name, str + *i, i);
	return (name);
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
}

int is_redirection(/*t_list *input, t_list *output, */ char *str, short type)
{
	t_redirection   red;
	char			*name;
	int             i;

	i = 0;
	//  red = malloc(sizeof(t_redirection));
	//  if (!red)
	//      return (0);
	//  red.fd = 0;
	//  red.mode = mode(type);
	while (str[i] && str[i] == ' ')
		i++;
	name = get_name(&str[i], &i, type);
	printf("%s\n", name);
	//   (type == 6 || type == 7) && add_node(input, input->last, red);
	//   (type == 8 || type == 9) && add_node(output, output->last, red);
	return (i);
}

int main()
{
	char	*l;
	while (1)
	{
		l = readline("> ");
		add_history(l);
		is_redirection(l, 6);
	}
}
