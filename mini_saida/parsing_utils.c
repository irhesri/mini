#include "h.h"
#include <fcntl.h>

short   is_special_red(char c)
{
    return (c == '|' || c == '<' ||c == '>' || c == ' ' || c == ';');
}

char    *is_quoted(char *str, int *len, char c)
{
    char    *res;

    res = my_strdup(&str[*len], c);
    (*len) += my_size(NULL, res);
    if (str[*len])
        (*len)++;
    return (res);
}

char *is_double_quoted(char *str, int *pos)
{
	char	*quote_val;
	char	*var;
	int		i;

	quote_val = NULL;
	while (str[*pos] && str[*pos] != 34)
	{
		i = *pos;
		while (str[*pos] && str[*pos] != 34 && str[*pos] != '$')
			(*pos)++;
		if (str[*pos] == '$' && ++(*pos))
		{
			var = var_expand(str, pos);
			quote_val = free_join(quote_val, my_strdup(&str[i], '$'), 0);
			quote_val = free_join(quote_val, var, 1);
		}
		else
			quote_val = free_join(quote_val, my_strdup(&str[i], str[*pos]), 0);
	}
	(str[*pos] == 34) && (*pos)++;
//	printf("|__%s__%c__|\n", quote_val, str[*pos]);
	return (quote_val);
}
