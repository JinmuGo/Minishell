/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:37 by jgo               #+#    #+#             */
/*   Updated: 2023/02/26 16:55:00 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"
#include "error.h"
#include "signal_controller.h"

void	s_cmd_executor(t_simple_cmd *simple_cmd)
{
	const t_simple_cmd_type type = is_built_in_cmd(simple_cmd->cmd);

	if (type != FT_EXTERNAL)
		built_in(simple_cmd, type);
}

void	cmd_executor(t_tree_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_system_call_err(pid);
	signal_controller(NULL, NULL, SIG_CHILD, pid);
	if (pid == 0)
	{
		// child
		
	}
	else
	{
		// parent
		// wait_pid
	}
}