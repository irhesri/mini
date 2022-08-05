#include "h.h"
#include <ctype.h>
#include <fcntl.h>

char    *ft_strjoin(char *str1, char *str2)
{
    int     i;
    char    *res;

    i = -1;
    res = malloc(my_size(NULL, str1) + my_size(NULL, str2) + 1);
    if (!res)
        exit(printf("allocation error\n"));
    while (*str1)
        res[++i] = *str1++;
    while (*str2)
        res[++i] = *str2++;
    res[++i] = '\0';
    return (res);
}

char    *vr_expand(char *str, int *size)
{
    int     i;
    char    c;
    char    *res;
    t_node  *node;

    res = str;
    (*size) = 1;
    if (is_digit(str[(*size)]))
    {
        c = str[++(*size)];
        str[(*size)] = '\0';
        str = my_strdup(str, '\0');
        res[(*size)] = c;
        return (ft_strjoin("$", str));
    }
    while (str[(*size)] && (is_digit(str[(*size)]) || is_alphabet(str[(*size)]) || str[(*size)] == '_'))
        (*size)++;
    if ((*size) == 1)
        return (NULL);
    c = str[(*size)];
    str[(*size)] = '\0';
    str = getenv(str + 1);
    res[(*size)] = c;
    return (str);
}

char    **split_expand(char *str, int *len)
{
    char    **ress;
    char    *res;

    // if (str[1] == 39 || str[1] == '"')
    //  return (is_double_quoted());
    res = vr_expand(str, len);
    ress = my_split(res, ' ', 0);
    free (res);
    return (ress);
}

short   is_special_red(char c)
{
    return (c == '|' || c == '<' ||c == '>' || c == ' ' || c == ';');
}

void	var_exist(char *str, int *pos)
{
	while (str[*pos] && str[*pos] != 34 && str[*pos] != '$')
		(*pos)++;
}

char    *is_quoted(char *str, int *len, char c)
{
    char    *res;

    res = my_strdup(str, c);
    (*len) += my_size(NULL, res) + 1;
    if (str[*len])
        (*len)++;
    return (res);
}

char *is_double_quoted(char *str, int *size)
{
	char	*quote_val;
	char	*var;
	int		pos;
	int		i;

	pos = 0;
	quote_val = NULL;
	while (str[pos] && str[pos] != 34)
	{
		i = pos;
		var_exist(str, &pos);
		if (str[pos] == '$')
		{
			var = vr_expand(str + pos, size);
			quote_val = free_join(quote_val, my_strdup(&str[i], str[pos]), 0);
			quote_val = free_join(quote_val, var, 1);
			pos += *size;
		}
		else
			quote_val = free_join(quote_val, my_strdup(&str[i], str[pos]), 0);
	}
	*size = pos + 1;
	return (quote_val);
}

/*
void	valide_name(t_list *env, char *name, char *str, int *i)
{
	char	**var;
	int		len;	

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

void	get_name(t_redirection *red, char *str, int *i, short type)
{
	char	*name;

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

int	mode(short type)
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

int	is_redirection(t_list *input, t_list *output,  char *str, short type)
{
	t_redirection	red;
	int				i;

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
	char *line;
	char *l;
	int i;

	line = readline("> ");
	printf("%s\n%d\n", is_double_quoted(line, &i), i);
}*/
