/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:54:03 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/10 14:54:07 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * MAXPATHLEN);
	if (!path)
		return ;
	get_errno(0);
	if (!getcwd(path, MAXPATHLEN) && get_errno(1))
	{
		perror("");
		return ;
	}
	printf("%s\n", path);
	free(path);
}
