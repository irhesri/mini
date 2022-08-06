#include "h.h"
#include <fcntl.h>

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
    (*len) = my_size(NULL, res) + 1;
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
			var = var_expand(str + pos, size);
			quote_val = free_join(quote_val, my_strdup(&str[i], str[pos]), 0);
			quote_val = free_join(quote_val, var, 1);
			pos += *size;
		}
		else
			quote_val = free_join(quote_val, my_strdup(&str[i], str[pos]), 0);
	}
	*size = pos + 2;
	return (quote_val);
}
