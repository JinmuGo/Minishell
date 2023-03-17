/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:56:45 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 16:54:29 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_CONTROLLER_H
# define SIGNAL_CONTROLLER_H

/* signal_init.c */
void	set_signal_init(int signum);
void	signal_init(struct sigaction *s_int, struct sigaction *s_quit);

/* signal)child.c */
void	signal_child(pid_t	pid);

/* signal_heredoc */
void	signal_heredoc(pid_t	pid);

/* signal_controller.c */
void	signal_controller(t_signal_flags flag, pid_t pid);

#endif