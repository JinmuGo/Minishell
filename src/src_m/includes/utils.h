/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:35 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 21:39:23 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* singleton.c */

t_meta	*singleton(void);

/* input.c */

void	prompt(void);

// debug.c 나중에 삭제 할 것
void	print_list(void *content);

/* utils.c */
char	*get_cur_dir(void);

/* prompt. c*/
char *make_prompt(void);

#endif