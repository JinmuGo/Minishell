/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:49 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 11:13:28 by jgo              ###   ########.fr       */
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


// 처음 중간 끝 일 때 pipe를 닫아주는 행동을 실행! 
void	pipe_executor(t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	if (sequence == FIRST)
	{
		// first // left
		prt_sc_err(pipe(execute->cur_fd));
		cmd_executor(node->left, execute, sequence);
		close(execute->cur_fd[WRITE]);
	}
	else if (sequence == MIDDLE)
	{
		// middle // left
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
