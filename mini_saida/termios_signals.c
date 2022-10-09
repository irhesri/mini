/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:00:16 by sben-chi          #+#    #+#             */
/*   Updated: 2022/10/09 15:05:26 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_sigint(int sig)
{
    write(1, "\n", 1);
    get_errno((sig * 0) + 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}


