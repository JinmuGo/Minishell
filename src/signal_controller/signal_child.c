/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:33:16 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 15:58:20 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "signal_controller.h"

void	set_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(EXIT_SIGINT);
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(EXIT_SIGQUIT);
	}
}

void	signal_child(pid_t	pid)
{
	sigset_t			mask;
	struct sigaction	s_int;
	struct sigaction	s_quit;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	s_int.sa_mask = mask;
	s_quit.sa_mask = mask;
	s_int.sa_flags = 0;
	s_quit.sa_flags = 0;
	if (pid == 0)
	{
		s_int.sa_handler = set_signal_child;
		s_quit.sa_handler = set_signal_child;
	}
	else
	{
		s_int.sa_handler = SIG_IGN;
		s_quit.sa_handler = SIG_IGN;
	}
	sigaction(SIGINT, &s_int, NULL);
	sigaction(SIGQUIT, &s_quit, NULL);
}
