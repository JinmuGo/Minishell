/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:56:45 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 21:52:17 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_CONTROLLER_H
# define SIGNAL_CONTROLLER_H


/* signal_init.c */
void	signal_init(void);

/* signal_controller.c */
void    signal_controller(t_signal_flags flag);

#endif