/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:00:54 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/17 17:06:35 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "signal_controller.h"

void	set_signal_heredoc(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

void	signal_heredoc(pid_t	pid)
{
	sigset_t			mask;
	struct sigaction	s_int;
	struct sigaction	s_quit;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	s_int.sa_mask = mask;
	s_quit.sa_mask = mask;
	if (pid == 0)
	{
		s_int.sa_handler = set_signal_heredoc;
		s_quit.sa_handler = SIG_IGN;
	}
	else
	{
		s_int.sa_handler = SIG_IGN;
		s_quit.sa_handler = SIG_IGN;
	}
	sigaction(SIGINT, &s_int, NULL);
	sigaction(SIGQUIT, &s_quit, NULL);
}
