#include "h.h"

void    valide_name(t_list *env, char *name, char *str, int *i)
{
    char    **var;
    int     len;

    var = NULL;
    while (str[*i] && !is_special_red(str[*i]))
    {
        if (str[*i] == 39)
            name = free_join(name, is_quoted(str + *i + 1, i, str[*i]), 0);
        else if (str[*i] == 34)
            name = free_join(name, is_double_quoted(str + *i + 1, i, str[*i]), 0);
        else if (str[*i] == '$')
        {
            var = split_expand(env, str, len);
            if (var + 1)
            {
                printf ("$: <file_name>: ambiguous redirect\n");
                name = NULL;
                return ;
            }
            name = free_join(name, *var, 1);
        }
    }
}

void    get_name(t_redirection *red, char *str, int *i, short type)
{
    char    *name;

    name = NULL;
    if (str[*i] && is_special_red(str[*i]) && str[*i] != '#')
    {
        printf("$: syntax error near unexpected token `%c'", str[*i]);
        return ;
    }
    if (type == 7)
    {
        while (str[*i] && str[*i] != ' ' && !is_special_red(str[*i]))
        {
            if (str[*i] && (str[*i] == 34 || str[*i] == 39))
                red->fd = -2;
            red->name = free_join(red->name, is_quoted(str + *i + 1, i, str[*i]), 0);
        }
    }
    else
        valide_name(red->name, str + *i, i);
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
        return (O_APPEND)
}

int is_redirection(t_list *input, t_list *output,  char *str, short type)
{
    t_redirection   red;
    int             i;

    i = 0;
    red = malloc(sizeof(t_redirection));
    if (!red)
        return (0);
    red.fd = 0;
    red.mode = mode(type);
    while (str[i] && str[i] == ' ')
        *i++;
    red.name = get_name(&red, &str[i], &i, type);
    (type == 6 || type == 7) && add_node(input, input->last, red);
    (type == 8 || type == 9) && add_node(output, output->last, red);
    return (i);
}

int main()
{
	char	*l;
	while (1)
	{
		l = readline(is_redirection(l, 7));
		add_history(l);
		printf("", );
	}
}
