/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_command.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:48:10 by jgo               #+#    #+#             */
/*   Updated: 2023/02/28 16:12:36 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_MVP_H
# define META_MVP_H

/* meta_receiver/c */
void    *meta_receiver(t_meta_flags flag, int arg);

/* meta_invoker.c */
t_meta *get_meta(void);
int     get_err_num(void);
t_hash_table *get_envp(void);
t_list  *get_unlink_lst(void);
int     *get_exit_status(void);
void    set_err_num(int arg);
void    set_exit_status(int arg);

#endif