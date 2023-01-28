/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:35 by jgo               #+#    #+#             */
/*   Updated: 2023/01/28 17:25:05 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* utils.c */

t_meta  *get_meta(void);

/* input.c */

void    prompt(void);

/* signal.c */

void	signal_process(int signum);

#endif