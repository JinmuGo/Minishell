/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:55:44 by jgo               #+#    #+#             */
/*   Updated: 2023/02/28 15:58:18 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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