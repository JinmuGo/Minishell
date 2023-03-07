/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by jgo               #+#    #+#             */
/*   Updated: 2023/03/06 21:59:32 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"
#include "meta_command.h"
#include "envp_command.h"

t_bool	is_built_in(t_tree_node *root)
{
	t_simple_cmd_type s_type;

	if (root == NULL || root->right == NULL || root->right->right == NULL)
		return (FT_FALSE);
	s_type = is_built_in_cmd(((t_simple_cmd *)((t_token *)(root->right->right->value))->cmd_val.simple_cmd)->cmd);
	if (s_type != FT_EXTERNAL)
		return (FT_TRUE);
	else
		return (FT_FALSE);
}

t_bool	is_single(t_tree_node *root)
{
	const t_token_type t_type = ((t_token *)(root->right->value))->type;

	if (t_type != PIPE)
		return (FT_TRUE);
	else
		return (FT_FALSE);
}

void	recursive_exec(t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	const t_token_type token_type = check_token_type(node);

	if (node == NULL || token_type != PIPE)
		return ;
	execute->child[LEFT] = check_token_type(node->left);
	execute->child[RIGHT] = check_token_type(node->right);
	pipe_executor(node, execute, sequence);
	sequence = MIDDLE;
	recursive_exec(node->right, execute, sequence);
}

void	shlvl_control(char *proc_name)
{
	int	val;

	if (ft_strcmp(proc_name, "./minishell"))
		return ;
	val = ft_atoi(get_envp_elem("SHLVL")->val);
	set_envp_elem("SHLVL", ft_itoa(val - 1));
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
		set_exit_status(WEXITSTATUS(exit_status));
		// printf("len : %d proc_name: %s   pid: %d\n", len, ((t_child_proc *)(tmp->content))->name, ((t_child_proc *)(tmp->content))->pid);
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
	execute->in_fd =  dup(STDIN_FILENO);
	execute->out_fd = dup(STDOUT_FILENO);
	execute->cur_fd[0] = -1;
	execute->cur_fd[1] = -1;
	execute->prev_fd[0] = -1;
	execute->prev_fd[1] = -1;
	execute->child_lst = NULL;
}

void    executor(t_tree *tree)
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
	// print_pipe(&execute);
}