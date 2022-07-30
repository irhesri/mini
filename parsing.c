// // #include "minishell.h"

// short	is_special(char *c)
// {
// 	if (*c == '<')
// 	{
// 		if (*(c + 1) == '<')
// 			return (1);
// 		return (2);
// 	}
// 	if (*c == '>')
// 	{
// 		if (*(c + 1) == '>')
// 			return (3);
// 		return (4);
// 	}
// 	if (*c == '$')
// 		return (5);
// 	if (*c == 34)
// 		return (6);
// 	if (*c == 39)
// 		return (7);
// 	if (*c == ' ' || *c == '|')
// 		return (8);
// }

// char	**get_arguments(t_data *data, char *str)
// {
// 	// i[0] indexe
// 	// i[1] special char number
// 	// i[2] len
// 	// i[3] pipe id
// 	int		i[5] = {0};
// 	int		index;
// 	char	**args;
// 	char	**ress;
// 	char	*res;
// 	t_list	*red;
// 	t_redirections	*reds;

// 	red = malloc(sizeof(t_list));
// 	red->head = NULL;
// 	red->last = NULL;

// 	i[0] = -1;
// 	data->n = 0;
// 	index = 0;
// 	while (str[++(i[0])])
// 	{
// 		i[1] = is_special(str + i[0]);
// 		if (i[1])
// 		{
// 			if (i[1] && i[1] < 5)
// 				i[2] = is_redirection(red, str + i[0] + 1 + i[1] % 2, i[1], i[3]);
// 			else if (i[1] == 5)
// 				ress = expand(data->env, str + i[0] + 1, i + 2, 1);
// 			else if (i[1] == 6)
// 				ress = is_double_quoted(str + i[0] + 1, i + 2);
// 			else if (i[1] == 7)
// 			{
// 				res = my_strdup(str + i[0] + 1, 39);
// 				i[2] = my_size(NULL, res);
// 			}
// 			else if (i[1] == 8)
// 				i[3]++;
// 			i[0] += i[2];
// 		}
// 		else
// 		{
// 			index = i[0];
// 			while (str[i[0]] && !is_special(str[i[0]]))
// 				i[0]++;
// 			if (index != i[0])
// 				res = my_strdup(str + index, str[i[0]]);
// 		}

// 	}
// 	// if (data->n == 1)
// 	// 	args = NULL;
// }


// // // arg = expand(env, my_strdup(str, '"'), len);
