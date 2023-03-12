/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:39:49 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/12 17:01:55 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "data_structure.h"

void	make_left(
	t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_tree_node	*next_node;

	next_node = NULL;
	if (cur_node == tree->root || ((t_token *)(cur_node->value))->type == S_CMD)
		return ;
	if (((t_token *)(cur_node->value))->type == PIPE)
		next_node = make_cmd_node(tree, cur_node, dque);
	else if (((t_token *)(cur_node->value))->type == CMD)
		next_node = make_rdr_node(tk_list, cur_node, dque);
	else if (((t_token *)(cur_node->value))->type == RDR)
		next_node = make_rdr_node(tk_list, cur_node, dque);
	if (next_node && next_node != cur_node)
		dque_to_tree(tree, tk_list, next_node, dque);
	return ;
}

void	make_right(
	t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_tree_node	*next_node;

	next_node = NULL;
	if (((t_token *)(cur_node->value))->type == RDR \
		|| ((t_token *)(cur_node->value))->type == S_CMD)
		return ;
	if (((t_token *)(cur_node->value))->type == PIPE)
	{
		next_node = make_pipe_node(tk_list, cur_node, dque);
		if (next_node && next_node == cur_node)
			next_node = make_cmd_node(tree, cur_node, dque);
	}
	else if (((t_token *)(cur_node->value))->type == CMD)
		next_node = make_s_cmd_node(tk_list, cur_node, dque);
	if (next_node && next_node != cur_node)
		dque_to_tree(tree, tk_list, next_node, dque);
}
