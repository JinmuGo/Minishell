/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/02/24 15:22:33 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

void	rdr_expander(t_rdr	*rdr)
{
	if (rdr == NULL)
		return ;
	if (rdr->rdr_type != HEREDOC)
	{
		rdr->file = shell_param_expand(rdr->file);
		rdr->file = quote_removal(rdr->file);
	}
}

void	cmd_expander(t_simple_cmd	*cmd)
{
	char	**args;

	if (cmd == NULL)
		return ;
	cmd->cmd = shell_param_expand(cmd->cmd);
	cmd->cmd = quote_removal(cmd->cmd);
	args = cmd->args;
	while (*args)
	{
		*args = shell_param_expand(*args);
		*args = quote_removal(*args);
		args++;
	}
}

/**
 * @brief 
 * 
 * @param token 
 */
void	expander_classify_token(t_tree_node	*node)
{
	const t_token *token = (t_token *)(node->value);

	if (token == NULL)
		return ;
	// RDR OR S_CMD만 확장한다.
	if (token->type == RDR)
		rdr_expander(token->cmd_val.rdr); // 모든 rdr을 확장한다.
	else if (token->type == S_CMD)
		cmd_expander(token->cmd_val.simple_cmd);
}

// executor 에서 tree를 받으면서 실행한다.
// 그리고 만약 노드의 타입이 CMD일 경우 expanding을 진행한다.
// expander에서 node의 값이 null이 아닐 때만 확장한다.

// 1. shell parameter expansion
// 2. Quote Removal
/**
 * @brief 
 * 
 * @param node // 트리안의 모든 노드를 돈다.
 */
void    expander(t_tree *tree)
{
	if (tree == NULL || tree->root == NULL)
		return ;
	tree->pre_order_traversal(tree->root, expander_classify_token);
}