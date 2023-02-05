/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/02/05 19:33:51 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

/**
 * @brief 
 * 
 * @param token 
 */
void	iter_token(t_token	*token)
{
	const	t_simple_cmd	*cmd = token->cmd_val.simple_cmd;
	char	*word;

	if (token->type != CMD)
		return ;
	
	
}


// executor 에서 tree를 받으면서 실행한다.
// 그리고 만약 노드의 타입이 CMD일 경우 expanding을 진행한다.
// expander에서 node의 값이 null이 아닐 때만 확장한다.

// 1. shell parameter expansion
// 2. Quote Removal
void    expander(t_tree_node *node)
{
	
	if (node == NULL)
		return ;	
	iter_token(node->value);
	expander(node->right);
	expander(node->left);
}