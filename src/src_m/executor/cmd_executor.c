/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:37 by jgo               #+#    #+#             */
/*   Updated: 2023/03/16 20:09:40 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"
#include "error.h"
#include "signal_controller.h"
#include "meta_command.h"
#include "data_structure.h"
#include "envp_command.h"

void	s_cmd_executor(\
	t_tree_node *node, const char **path_arr, const char **envp_arr)
{
	char				*abs_path;
	t_simple_cmd_type	type;
	t_simple_cmd		*simple_cmd;

	if (node == NULL || node->value == NULL)
		exit(EXIT_FAILURE);
	simple_cmd = ((t_token *)(node->value))->cmd_val.simple_cmd;
	if (simple_cmd == NULL)
		exit(EXIT_FAILURE);
	type = is_built_in_cmd(simple_cmd->cmd);
	if (type != FT_EXTERNAL)
		exit(built_in(simple_cmd, type));
	else
	{
		abs_path = make_abs_path(simple_cmd->cmd, path_arr);
		execve(abs_path, simple_cmd->args, (char **)envp_arr);
		prt_built_in_err(simple_cmd->cmd, NULL, ERR_CMD_NOT_FOUND, 127);
		exit(127);
	}
}

void	direction_handler(t_executor *execute, t_sequence sequence)
{
	if (sequence == FIRST)
	{
		dup2(execute->cur_fd[WRITE], STDOUT_FILENO);
		close(execute->cur_fd[READ]);
	}
	else if (sequence == MIDDLE)
	{
		dup2(execute->prev_fd[READ], STDIN_FILENO);
		dup2(execute->cur_fd[WRITE], STDOUT_FILENO);
		close(execute->cur_fd[READ]);
	}
	else
	{
		dup2(execute->cur_fd[READ], STDIN_FILENO);
		close(execute->cur_fd[WRITE]);
	}
}

void	post_process(t_executor *execute, t_tree_node *node, pid_t pid)
{
	t_child_proc	*child_proc;

	child_proc = ft_malloc(sizeof(t_child_proc));
	child_proc->pid = pid;
	if (node)
		child_proc->name = (\
			((t_token *)(node->value))->cmd_val.simple_cmd->cmd);
	else
		child_proc->name = NULL;
	ft_lstadd_back(&execute->child_lst, ft_lstnew(child_proc));
}

void	cmd_executor(\
	t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	const char		**path_arr = get_path_arr();
	const char		**envp_arr = make_envp_arr(node->right);
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		prt_sc_err(pid);
	signal_controller(SIG_CHILD, pid);
	if (pid == 0)
	{
		direction_handler(execute, sequence);
		rdr_executor(node->left, execute);
		s_cmd_executor(node->right, path_arr, envp_arr);
	}
	else
	{
		post_process(execute, node->right, pid);
		if (path_arr)
			ft_free_all_arr((void *)path_arr);
		if (envp_arr)
			ft_free_all_arr((void *)envp_arr);
	}
}
