/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:44:32 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/11 18:21:48 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc_case(char *str, t_redirection *red, int *i)
{
	static int	nbr_heredoc;

	red->fd = -2;
	get_errno(0);
	++nbr_heredoc;
	if (nbr_heredoc > 16 && get_errno(2))
	{
		print_error("maximum here-document count exceeded\n", NULL);
		reset_exit(2);
	}
	while (str[*i] && !is_special_red(str[*i]))
	{
		if (str[*i] && (str[*i] == 34 || str[*i] == 39) && (*i)++)
		{
			red->fd = -3;
			red->name = free_join(red->name, is_quoted(str, i, str[*i - 1]), 0);
		}
		else
			red->name = free_join(red->name, normal_chars(str, i, 1), 0);
	}
	return (1);
}

int	valide_name(char **name, char *str, int *i)
{
	char	**var;
	int		k;

	var = NULL;
	while (str[*i] && !is_special_red(str[*i]))
	{
		if (str[*i] == 39 && ++(*i))
			*name = free_join(*name, is_quoted(str, i, str[*i - 1]), 0);
		else if (str[*i] == 34 && ++(*i))
			*name = free_join(*name, is_double_quoted(str, i), 0);
		else if (str[*i] == '$' && ++(*i))
		{
			k = *i - 1;
			var = split_expand(str, i);
			if (*(var + 1))
			{	
				ft_error(str, name, &k);
				return (0);
			}
			*name = free_join(*name, *var, 1);
		}
		else
			*name = free_join(*name, normal_chars(str, i, 0), 0);
	}
	return (1);
}

void	error_msg(char *str, int i)
{
	char	c[2];

	if (!str[i + 1])
		print_error("syntax error near unexpected token `newline'\n", NULL);
	else
	{
		c[0] = str[i];
		c[1] = '\0';
		print_error("syntax error near unexpected token `", ft_strjoin(c, "'\n"));
	}
}

short	get_name(t_redirection *red, char *str, int *i, short type)
{
	int	k;

	k = *i + 1;
	if (str[*i] && (is_special_red(str[*i]) || str[*i] == '#'))
	{
		error_msg(str, *i);
		red->name = NULL;
		return (get_errno(258));
	}
	(type == 7) && here_doc_case(str, red, i);
	if (str[*i] == '$' && !var_expand(str, &k))
	{
		red->fd = -4;
		return (1);
	}
	if ((type != 7) && !(valide_name(&(red->name), str, i)))
		red->fd = -4;
	return (0);
}

short	is_redirection(t_pipe *pipe, char *str, int *i, short type)
{
	t_redirection	*red;
	short			exit_val;

	red = malloc(sizeof(t_redirection));
	if (!red)
		reset_exit(1);
	(*i) += (type % 2);
	red->fd = 0;
	red->mode = (((type == 8) * O_TRUNC) + ((type == 9) * O_APPEND));
	red->name = NULL;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	exit_val = get_name(red, str, i, type);
	add_node(pipe->redirections, pipe->redirections->last, red);
	return (exit_val);
}
