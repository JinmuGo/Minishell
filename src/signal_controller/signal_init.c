/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:55:44 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 17:06:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include <errno.h>

void	set_signal_init(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_init(struct sigaction *s_int, struct sigaction *s_quit)
{
	sigset_t		mask;
	struct termios	term_attr;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	s_int->sa_mask = mask;
	s_int->sa_handler = set_signal_init;
	s_quit->sa_mask = mask;
	s_quit->sa_handler = SIG_IGN;
	sigaction(SIGINT, s_int, NULL);
	sigaction(SIGQUIT, s_quit, NULL);
	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}
