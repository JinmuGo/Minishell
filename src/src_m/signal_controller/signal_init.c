/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:55:44 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 10:27:28 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include <errno.h>

void    set_signal_init(int signum)
{
    if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signum == SIGQUIT)
		rl_on_new_line();
	rl_redisplay();
}

void    signal_init(struct sigaction *s_int, struct sigaction *s_quit)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	s_int->sa_mask = mask;
	s_int->sa_handler = set_signal_init;
	s_quit->sa_mask = mask;
	s_quit->sa_handler = SIG_IGN;
	sigaction(SIGINT, s_int, NULL);
	sigaction(SIGQUIT, s_quit, NULL);
}