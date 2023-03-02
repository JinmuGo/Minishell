/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:51:16 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 20:51:07 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void    executor(t_tree *tree);

/* is_built_in_cmd.c */

t_simple_cmd_type	is_built_in_cmd(char *cmd);

/* $(TYPE)_executor.c */
void    rdr_executor(t_tree_node *node, t_executor *execute);
void	rdr_restore(t_executor *execute);
void	pipe_executor(t_tree_node	*node, t_executor *execute);
void	cmd_executor(t_tree_node *node, t_executor *execute, t_tree_edge edge);

/* executor_utils.c */
t_token_type	check_token_type(t_tree_node *node);

/* exit status */
# define EXIT_COM_NOT_FOUND 127
# define EXIT_SIGINT 130 // 128 + 2
# define EXIT_SIGQUIT 131 // 128 + 3
# define EXIT_SIGTERM 143 // 128 + 15

// rdr실행할 때 error 처리 
# define ERR_TOO_LONG ": File name too long"


#endif