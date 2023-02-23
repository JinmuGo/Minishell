/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 21:33:21 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"

void	executor_classify_token(t_tree_node	*node)
{
	const t_token *token = (t_token *)(node->value);

	if (token->type == RDR)
		rdr_executor(token->cmd_val.rdr);
	else if (token->type == PIPE)
		pipe_executor(token->cmd_val.pipe);
	else if (token->type == S_CMD)
		s_cmd_executor(token->cmd_val.simple_cmd);
}

t_bool	is_single_built_in(t_tree_node *root)
{
	const t_token_type type = ((t_token *)(root->right->value))->type;

	if (type == PIPE)
		return (FT_FALSE);
	else
		return (FT_TRUE);
}

void    executor(t_tree *tree)
{
	const t_bool s_built_in = is_single_built_in(tree->root);

	if (s_built_in)
		tree->pre_order_traversal(tree->root->right, executor_classify_token);
	else
		tree->pre_order_traversal(tree->root, executor_classify_token);
}