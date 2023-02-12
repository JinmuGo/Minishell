/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_command.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:55:00 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 12:52:50 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_MVP_H
# define ENVP_MVP_H

/* envp_receiver_method.c */
t_hash_elem *hash_get(t_hash_table *ht, char *key);
void    hash_insert(t_hash_table *ht, char *key, char *val);
void    hash_resize(t_hash_table *ht);
void	hash_delete(t_hash_table *ht, char *key);

/* envp_receiver_utils.c */
t_bool  hash_put(t_hash_elem *elem, char *key, char *val);
void    init_hash_table(t_hash_table *ht);
void    free_bucket(t_hash_table *ht);
t_bool  is_same_key(char *origin, char *judge);
t_hash_asset    hash_asset_init(t_hash_table *ht, char *str);

/* envp_receiver.c */
t_hash_elem *envp_receiver(t_envp_flags flag, char *key, char *val);

/* envp_receiver_init.c*/
void	envp_init(char **envp);

/* envp_invoker.c */
void	set_envp_elem(char *key, char *val);
t_hash_elem	*get_envp_elem(char *key);
void	del_envp_elem(char *key);

// debug
void display(t_hash_table *ht);

#endif