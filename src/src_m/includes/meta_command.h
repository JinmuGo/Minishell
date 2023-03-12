/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_command.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:48:10 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:41:19 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_COMMAND_H
# define META_COMMAND_H

/* meta_receiver/c */
void			*meta_receiver(t_meta_flags flag, int arg, char *str);

/* meta_invoker.c */
t_hash_table	*get_envp(void);
t_meta			*get_meta(void);
int				get_err_num(void);
t_list			**get_unlink_lst(void);
int				*get_exit_status(void);
char			*get_cur_dir(void);
void			set_err_num(int arg);
void			set_exit_status(int arg);
void			set_cur_dir(char *str);

#endif