/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:17:11 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 15:33:14 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

void    s_built_in_exec(t_tree_node *root, t_executor *execute);
void    built_in(t_simple_cmd *simple_cmd, t_simple_cmd_type type);

void ft_echo(t_simple_cmd *simple_cmd);
void ft_cd(t_simple_cmd *simple_cmd);
void ft_pwd(t_simple_cmd *simple_cmd);
void ft_export(t_simple_cmd *simple_cmd);
void ft_unset(t_simple_cmd *simple_cmd);
void ft_env(t_simple_cmd *simple_cmd);
void ft_exit(t_simple_cmd *simple_cmd);

t_bool	is_valid_params(char c);

#endif