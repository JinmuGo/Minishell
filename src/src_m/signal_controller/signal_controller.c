/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:21:28 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 18:35:37 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "signal_controller.h"

void    signal_controller (struct sigaction *s_int, struct sigaction *s_quit, t_signal_flags flag, ...)
{
	va_list	ap;
	int	pid;

	va_start(ap, flag);
	pid = va_arg(ap, int);
	if (flag == SIG_INIT)
		signal_init(s_int, s_quit);
	else if (flag == SIG_CHILD)
		signal_child(pid);
	va_end(ap);
}