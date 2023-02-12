/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:35 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 12:27:09 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* singleton.c */

t_meta	*singleton(void);

/* input.c */

void	prompt(void);

/* signal.c */

void	signal_process(int signum);

// debug.c

void	print_list(void *content);

#endif