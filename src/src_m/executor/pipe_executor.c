/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:49 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 21:36:21 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include <errno.h>
#include "executor.h"
#include "meta_command.h"


// right로 들어갈 때
// pipe node의 right pipe node이면 curfd 를 prevfd로 변경한 뒤 curfd에 pipe(cur_fd)를 해준다.
// pipe node의 right cmd node일 경우 prevfd로 변경한 뒤 cur_fd[1]에 STDOUT을 넣는다.

// left로 들어갈 때
// pipe node의 right 없을 경우 curfd 를 prevfd로 변경한 뒤 cur_fd[1]에 STDOUT을 넣는다.
// 0 left 1 right


void	pipe_executor(t_tree_node *node, t_executor *execute)
{
	const t_token_type type[2] = {check_token_type(node->left),check_token_type(node->right)};
	pid_t	pid_l;
	pid_t	pid_r;

	pid_l = 0;
	pid_r = 0;
	execute->edge[LEFT] = type[LEFT];
	execute->edge[RIGHT] = type[RIGHT];
	execute->prev_fd[READ] = execute->cur_fd[READ];
	execute->prev_fd[WRITE] = execute->cur_fd[WRITE];
	
	if (type[RIGHT] == NONE || (node->right == NULL && type[RIGHT] == CMD))
		execute->cur_fd[WRITE] = STDOUT_FILENO;
	else
		print_system_call_err(pipe(execute->cur_fd));
	// pipe_process
	if (type[LEFT] == CMD)
	{
		cmd_executor(node->left, execute, LEFT);
	}
	if (type[RIGHT] == CMD)
	{
		cmd_executor(node->left, execute, RIGHT);
	}
}
