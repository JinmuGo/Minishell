/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 19:57:36 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
// RDR = 0,
// PIPE = 1,
// S_CMD = 4,
void    rdr_executor(t_rdr *rdr)
{

}

void	pipe_executor(t_pipe *pipe)
{

}

void	s_cmd_executor(t_simple_cmd *simple_cmd)
{
	const t_simple_cmd_type type = is_built_in_cmd(simple_cmd->cmd);

	if (type != FT_EXTERNAL)
	{
		
	}
		
}

void    executor(t_tree_node *node)
{
	if (node == NULL)
		return ;

	


	executor(node->left);
	executor(node->right);
}