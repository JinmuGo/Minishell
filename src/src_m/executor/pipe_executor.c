/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:49 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 10:19:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include <errno.h>
#include "executor.h"
#include "meta_command.h"

void	pipe_executor(\
	t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	if (node == NULL)
		return ;
	if (sequence == FIRST)
	{
		prt_sc_err(pipe(execute->cur_fd));
		cmd_executor(node->left, execute, sequence);
		close(execute->cur_fd[WRITE]);
	}
	else if (sequence == MIDDLE)
	{
		prt_sc_err(pipe(execute->cur_fd));
		cmd_executor(node->left, execute, sequence);
		close(execute->prev_fd[READ]);
		close(execute->cur_fd[WRITE]);
	}
	execute->prev_fd[READ] = execute->cur_fd[READ];
	execute->prev_fd[WRITE] = execute->cur_fd[WRITE];
	if (execute->child[RIGHT] == CMD)
	{
		sequence = LAST;
		cmd_executor(node->right, execute, sequence);
		close(execute->cur_fd[READ]);
		close(execute->cur_fd[WRITE]);
	}
}
