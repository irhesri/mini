/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:54:03 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/16 12:12:23 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * MAXPATHLEN);
	if (!path)
		exit (write(1, "allocation error\n", 17));
	get_errno(0);
	if (!getcwd(path, MAXPATHLEN) && get_errno(1))
	{
		free(path);
		perror(get_bash_name(NULL));
		return ;
	}
	write(1, path, my_size(NULL, path));
	write(1, "\n", 1);
	free(path);
}
