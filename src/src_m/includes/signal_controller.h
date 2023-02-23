/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:56:45 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 17:51:50 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_CONTROLLER_H
# define SIGNAL_CONTROLLER_H


/* signal_init.c */
void    signal_init(struct sigaction *s_int, struct sigaction *s_quit);

/* signal)child.c */
void signal_child(int pid);

/* signal_controller.c */
void    signal_controller (struct sigaction *s_int, struct sigaction *s_quit, t_signal_flags flag, ...);

#endif