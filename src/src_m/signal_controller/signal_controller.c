/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:21:28 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 10:12:35 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "signal_controller.h"

void    signal_controller (t_signal_flags flag, ...)
{
	va_list	ap;
	pid_t	pid;
	struct sigaction s_int;
	struct sigaction s_quit;

	va_start(ap, flag);
	pid = va_arg(ap, pid_t);
	if (flag == SIG_INIT)
		signal_init(&s_int, &s_quit);
	else if (flag == SIG_CHILD)
		signal_child(pid);
	va_end(ap);
}