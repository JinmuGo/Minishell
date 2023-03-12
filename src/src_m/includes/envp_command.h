/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_command.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:55:00 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:45:04 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_COMMAND_H
# define ENVP_COMMAND_H

/* envp_receiver_method.c */
t_hash_elem		*hash_get(t_hash_table *ht, const char *key);
void			hash_insert(t_hash_table *ht, const char *key, const char *val);
void			hash_delete(t_hash_table *ht, const char *key);
void			hash_print_all(const char *option, t_hash_table *ht);
char			**hash_convert_arr(t_hash_table *ht);

/* envp_receiver_utils.c */
void			free_bucket(t_hash_table *ht);
t_bool			hash_put(t_hash_elem *elem, const char *key, const char *val);
t_bool			is_same_key(const char *origin, const char *judge);
t_hash_asset	hash_asset_init(t_hash_table *ht, const char *str);
void			hash_resize(t_hash_table *ht);

/* envp_receiver.c */
t_hash_elem		*envp_receiver(\
	t_envp_flags flag, const char *key, const char *val, const char *option);

/* envp_receiver_init.c*/
void			envp_init(char **envp);
char			*get_envp_key(char *envp_elem);
char			*get_envp_val(char *envp_elem);

/* envp_invoker.c */
void			set_envp_elem(const char *key, const char *val);
t_hash_elem		*get_envp_elem(const char *key);
void			del_envp_elem(const char *key);
void			print_envp_elem(const char *option);
char			**convert_char_arr(void);

#endif