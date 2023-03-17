/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 16:31:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"
#include "meta_command.h"
#include "envp_command.h"
#include "signal_controller.h"

void	recursive_exec(
	t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	const t_token_type	token_type = check_token_type(node);

	if (node == NULL || token_type != PIPE)
		return ;
	execute->child[LEFT] = check_token_type(node->left);
	execute->child[RIGHT] = check_token_type(node->right);
	pipe_executor(node, execute, sequence);
	sequence = MIDDLE;
	recursive_exec(node->right, execute, sequence);
}

void	wait_child(t_executor *execute)
{
	int		len;
	int		exit_status;
	t_list	*node;
	t_list	*tmp;

	node = execute->child_lst;
	len = ft_lstsize(execute->child_lst);
	while (len)
	{
		tmp = node;
		waitpid(((t_child_proc *)(tmp->content))->pid, &exit_status, 0);
		if (WIFSIGNALED(exit_status))
			set_exit_status(exit_status + 128);
		else
			set_exit_status(WEXITSTATUS(exit_status));
		shlvl_control(((t_child_proc *)(tmp->content))->name);
		node = node->next;
		ft_lstdelone(tmp, free);
		len--;
	}
	ft_lstdelone(node, free);
}

void	execute_init(t_tree *tree, t_executor *execute)
{
	execute->single = is_single(tree->root);
	if (execute->single)
		execute->built_in = is_built_in(tree->root);
	else
		execute->built_in = FT_FALSE;
	execute->in_fd = dup(STDIN_FILENO);
	execute->out_fd = dup(STDOUT_FILENO);
	execute->cur_fd[0] = -1;
	execute->cur_fd[1] = -1;
	execute->prev_fd[0] = -1;
	execute->prev_fd[1] = -1;
	execute->child_lst = NULL;
}

void	executor(t_tree *tree)
{
	t_executor	execute;

	if (tree == NULL || tree->root == NULL)
		return ;
	execute_init(tree, &execute);
	if (execute.built_in && execute.single)
		s_built_in_exec(tree->root, &execute);
	else if (execute.single)
		cmd_executor(tree->root->right, &execute, FIRST);
	else
		recursive_exec(tree->root->right, &execute, FIRST);
	if (execute.child_lst)
		wait_child(&execute);
	rdr_restore(&execute);
}
