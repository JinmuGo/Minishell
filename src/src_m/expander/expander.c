/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/02/07 18:28:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

void	rdr_expander(t_rdr	*rdr)
{
	if (rdr->rdr_type != HEREDOC)
		shell_param_expand(rdr->file);
	rdr->quote = quote_removal(rdr->file);
}

void	cmd_expander(t_simple_cmd	*cmd)
{
	char	**args;

	shell_param_expand(cmd->cmd);
	quote_removal(cmd->cmd);
	args = cmd->args;
	while (*args)
	{
		shell_param_expand(*args);
		quote_removal(*args);
		args++;
	}
}

/**
 * @brief 
 * 
 * @param token 
 */
void	iter_token(t_token	*token)
{
	// RDR OR CMD만 확장한다.
	if (token->type == RDR)
		rdr_expander(token->cmd_val.rdr); // 모든 rdr을 확장한다.
	else if (token->type == CMD)
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
void    expander(t_tree_node *node)
{
	
	if (node == NULL)
		return ;	
	iter_token(node->value);
	expander(node->right);
	expander(node->left);
}