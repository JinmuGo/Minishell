/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:55:44 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 21:56:46 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    signal_init(void)
{
    signal(SIGQUIT, set_signal_init);
	signal(SIGINT, set_signal_init);
}