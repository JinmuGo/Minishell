/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:35 by jgo               #+#    #+#             */
/*   Updated: 2023/01/29 15:15:24 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* utils.c */

t_meta  *get_meta(void);
void	envp_init(char **envp);

/* input.c */

void    prompt(void);

/* signal.c */

void	signal_process(int signum);

// debug.c

void    print_list(void *content);

#endif