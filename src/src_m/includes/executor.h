/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:51:16 by jgo               #+#    #+#             */
/*   Updated: 2023/02/28 17:20:46 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void    executor(t_tree *tree);

/* is_built_in_cmd.c */

t_simple_cmd_type	is_built_in_cmd(char *cmd);

/* $(TYPE)_executor.c */
void    rdr_executor(t_tree_node *node);
void	pipe_executor(t_pipe *pipe);
void	cmd_executor(t_tree_node *node);

/* exit status */
# define EXIT_COM_NOT_FOUND 127
# define EXIT_SIGINT 130 // 128 + 2
# define EXIT_SIGQUIT 131 // 128 + 3
# define EXIT_SIGTERM 143 // 128 + 15

// rdr실행할 때 error 처리 
# define ERR_TOO_LONG ": File name too long"


#endif