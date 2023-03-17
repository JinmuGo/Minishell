/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:51:16 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 14:53:10 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void				executor(t_tree *tree);

/* is_built_in_cmd.c */

t_simple_cmd_type	is_built_in_cmd(char *cmd);

/* $(TYPE)_executor.c */
void				rdr_executor(t_tree_node *node, t_executor *execute);
void				rdr_restore(t_executor *execute);
void				pipe_executor(\
	t_tree_node *node, t_executor *execute, t_sequence sequence);
void				cmd_executor(\
	t_tree_node *node, t_executor *execute, t_sequence sequence);

/* executor_utils.c */
t_token_type		check_token_type(t_tree_node *node);
t_bool				is_built_in(t_tree_node *root);
t_bool				is_single(t_tree_node *root);
void				shlvl_control(char *proc_name);

/* cmd_executor_utils.c */
const char			**get_path_arr(void);
char				*make_abs_path(char *cmd, const char **path_arr);
const char			**make_envp_arr(t_tree_node *node);

#endif