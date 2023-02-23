/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:33:16 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 17:59:17 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"

void	set_signal_child(int sig)
{
    
	(void)sig;
	printf("\n");
	set_exit_status(EXIT_SUCCESS); // child의 exit status에 따라 다르게 처리해야함. ㅇ지금은 default 로 둔다. 
	// child_asset_free();
	exit (EXIT_SUCCESS);
}

// child의  signal을 처리하지만 child가 실행될 때 main shell의 상태도 함께 처리한다. ㄴ
void signal_child(int pid)
{
    sigset_t			mask;
	struct sigaction	s_int;
	struct sigaction	s_quit;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	s_int.sa_mask = mask;
	if (pid == 0)
		s_int.sa_handler = set_signal_child;
	else
		s_int.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_int, NULL);
	s_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_quit, NULL);
}